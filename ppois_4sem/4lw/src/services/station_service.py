from typing import List, Optional
from ..database.models import StationCreate, StationResponse
from ..database.repositories import IStationRepository

# Сервис с бизнес-логикой (SRP)
class StationService:
    def __init__(self, repo: IStationRepository):
        self.repo = repo
    
    def create_station(self, station: StationCreate) -> StationResponse:
        success = self.repo.add_station(station.name, station.line)
        if not success:
            raise ValueError("Station name already exists")
        # Получаем последнюю добавленную станцию (пример логики)
        return self.get_all_stations()[-1]
    
    def get_station(self, station_id: int) -> Optional[StationResponse]:
        data = self.repo.get_station(station_id)
        return StationResponse(**data) if data else None
    
    def get_all_stations(self) -> List[StationResponse]:
        stations = self.repo.get_all_stations()
        return [StationResponse(**s) for s in stations]