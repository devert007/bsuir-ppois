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

@app.post("/create_station")
async def create_station(station: StationCreate):
    success = db.add_station(station.name, station.line)
    if not success:
        raise HTTPException(status_code=400, detail="Station name already exists")
    return {"message": "Station created successfully"}


@app.get("/station/{station_id}", response_class=HTMLResponse)  # Измените response_class
async def get_station(station_id: int, request: Request): 
    station = db.get_station(station_id)
    if not station:
        raise HTTPException(status_code=404, detail="Station not found")
    return templates.TemplateResponse(
        "station.html",
        {"request": request, "station": station}
    )

@app.get("/choose_station")
async def choose_station():
  stations = db.get_all_stations()
  return {"stations": stations}
# @app.get("/create_passenger")
# def create_passenger():



if __name__ == "__main__":
  uvicorn.run("main:app",reload=True)