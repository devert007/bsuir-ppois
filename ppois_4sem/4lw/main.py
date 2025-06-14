from fastapi import FastAPI, Request, HTTPException
from fastapi.staticfiles import StaticFiles
from fastapi.responses import FileResponse
from fastapi.responses import HTMLResponse

from src.database.db_utils import StationDB
from pydantic import BaseModel
from fastapi.middleware.cors import CORSMiddleware
from fastapi.templating import Jinja2Templates

import uvicorn 

app = FastAPI(
    title="Metro System API",
    description="API for managing a metro system with stations, passengers, and trains",
    version="1.0.0"
)
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # Для разработки разрешите все источники
    allow_methods=["*"],
    allow_headers=["*"],
)
db = StationDB()

app.mount("/static", StaticFiles(directory="static"), name="static")
templates = Jinja2Templates(directory="templates")  
@app.get("/", response_class=FileResponse)
async def menu():
    return FileResponse("static/index.html")

class StationCreate(BaseModel):
    name: str
    line: str
class PassengerCreate(BaseModel):
    name: str

class BalanceUpdate(BaseModel):
    amount: float

class TariffUpdate(BaseModel):
    tariff_id: int

class StatusUpdate(BaseModel):
    is_active: bool
@app.post("/create_station")
async def create_station(station: StationCreate):
    success = db.add_station(station.name, station.line)
    if not success:
        raise HTTPException(status_code=400, detail="Station name already exists")
    return {"message": "Station created successfully"}


@app.get("/station/{station_id}", response_class=HTMLResponse) 
async def get_station(station_id: int, request: Request): 
    station = db.get_station(station_id)
    if not station:
        raise HTTPException(status_code=404, detail="Station not found")
    return templates.TemplateResponse(
        "station.html",
        {"request": request, "station": station}
    )
@app.delete("/station/{station_id}")
async def delete_station(station_id: int):
    success = db.delete_station(station_id)
    if not success:
        raise HTTPException(status_code=404, detail="Station not found")
    return {"message": "Station deleted successfully"}
@app.get("/choose_station")
async def choose_station():
  stations = db.get_all_stations()
  return {"stations": stations}




@app.post("/stations/{station_id}/passengers")
async def create_passenger(station_id: int, passenger: PassengerCreate):
    if not db.get_station(station_id):
        raise HTTPException(404, detail="Station not found")
    
    success = db.add_passenger(passenger.name, station_id)
    if not success:
        raise HTTPException(400, detail="Failed to create passenger")
    return {"message": "Passenger created successfully"}

@app.get("/stations/{station_id}/passengers")
async def get_passengers(station_id: int):
    passengers = db.get_passengers_by_station(station_id)
    return {"passengers": passengers}

@app.patch("/passengers/{passenger_id}/balance")
async def update_balance(passenger_id: int, update: BalanceUpdate):
    passenger = db.get_passenger(passenger_id)  
    if not passenger:
        raise HTTPException(404, detail="Passenger not found")
    
    if update.amount < 0 and abs(update.amount) > passenger['balance']:
        raise HTTPException(400, detail="Insufficient funds")
    
    success = db.update_passenger_balance(passenger_id, update.amount)
    if not success:
        raise HTTPException(400, detail="Balance update failed")
    
    return {"message": "Balance updated successfully"}

@app.patch("/passengers/{passenger_id}/tariff")
async def update_tariff(passenger_id: int, update: TariffUpdate):
    tariffs = [t["id"] for t in db.get_tariffs()]
    if update.tariff_id not in tariffs:
        raise HTTPException(400, detail="Invalid tariff ID")
    
    success = db.update_passenger_tariff(passenger_id, update.tariff_id)
    if not success:
        raise HTTPException(404, detail="Passenger not found")
    return {"message": "Tariff updated successfully"}

@app.patch("/passengers/{passenger_id}/status")
async def update_status(passenger_id: int):
    success = db.toggle_passenger_status(passenger_id)
    if not success:
        raise HTTPException(404, detail="Passenger not found")
    return {"message": "Status updated successfully"}

@app.get("/tariffs")
async def get_tariffs():
    return db.get_tariffs()




if __name__ == "__main__":
  uvicorn.run("main:app",reload=True)