from pydantic import BaseModel

class StationCreate(BaseModel):
    name: str
    line: str

class StationResponse(StationCreate):
    id: int