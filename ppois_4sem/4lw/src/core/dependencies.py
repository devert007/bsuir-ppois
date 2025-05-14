from fastapi import Depends
from ..database.repositories import StationRepository
from ..services.station_service import StationService

def get_repository() -> IStationRepository:
    return StationRepository()

def get_service(repo: IStationRepository = Depends(get_repository)) -> StationService:
    return StationService(repo)