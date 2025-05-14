async function createStation() {
  const name = document.getElementById('station-name').value;
  const line = document.getElementById('station-line').value;

  if (!name || !line) {
      alert("Please fill in both fields");
      return;
  }

  try {
      const response = await fetch('/create_station', {
          method: 'POST',
          headers: {
              'Content-Type': 'application/json',
          },
          body: JSON.stringify({ name, line }),
      });
      const result = await response.json();

      if (response.ok) {
          alert(result.message);
          document.getElementById('station-name').value = '';
          document.getElementById('station-line').value = '';
          loadStations(); 
      } else {
          alert(result.detail || "Error creating station");
      }
  } catch (error) {
      alert("Error creating station: " + error.message);
  }
}

let selectedStationId = null;

    async function loadStations() {
        try {
            const response = await fetch('/choose_station');
            const data = await response.json();
            const stationList = document.getElementById('stationList');
            stationList.innerHTML = '';

            data.stations.forEach(station => {
                const div = document.createElement('div');
                div.className = 'station-item';
                div.innerHTML = `
                    <h3>${station.name}</h3>
                    <p>Line: ${station.line}</p>
                `;
                
                // Обработчик выбора станции
                div.addEventListener('click', () => {
                  document.querySelectorAll('.station-item').forEach(item => {
                      item.classList.remove('selected');
                  });
                  div.classList.add('selected');
                  selectedStationId = station.id;  
              });

                stationList.appendChild(div);
            });
        } catch (error) {
            console.error("Error loading stations:", error);
        }
    }

    // Обработчик для кнопки "Choose station"
    document.getElementById('chooseStationBtn').addEventListener('click', (e) => {
      e.preventDefault();
      if (!selectedStationId) {
          alert("Please select a station first!");
          return;
      }
      window.location.href = `/station/${selectedStationId}`;  
  });

window.onload = loadStations;