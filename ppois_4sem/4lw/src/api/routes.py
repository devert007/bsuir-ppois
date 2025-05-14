from fastapi import APIRouter, Request, HTTPException
from fastapi.templating import Jinja2Templates
from ..core.dependencies import get_service
from ..database.models import StationCreate

router = APIRouter()
templates = Jinja2Templates(directory="templates")

@router.post("/create_station")
async def create_station(
    station: StationCreate,
    service: StationService = Depends(get_service)
):
    try:
        created = service.create_station(station)
        return {"message": "Station created", "data": created}
    except ValueError as e:
        raise HTTPException(400, detail=str(e))

@router.get("/station/{station_id}")
async def get_station(
    station_id: int,
    request: Request,
    service: StationService = Depends(get_service)
):
    station = service.get_station(station_id)
    if not station:
        raise HTTPException(404, detail="Station not found")
    return templates.TemplateResponse(
        "station.html", 
        {"request": request, "station": station}
    )