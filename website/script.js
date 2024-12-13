// script.js

document.getElementById('wildlifeForm').addEventListener('submit', async function(event) {
    event.preventDefault(); // Prevent form from submitting normally
    // Gather form data
    const ndvi = document.getElementById("ndvi").value;
    const nightlight = document.getElementById("nightlight").value;
    const area = document.getElementById("area").value;
    const chital = document.getElementById("chital").value;
    const sambar = document.getElementById("sambar").value;
    // const barkingDeer = document.getElementById("barking-deer").value;

    //const apiUrl = 'http://3.89.225.74:8080/predict';
    const apiUrl = 'https://hqsxh4rm20.execute-api.us-east-1.amazonaws.com/try/predict';
    
    const requestBody = {
        prey: 500,
        ndvi: 500,
        nightlight: 500,
        area: 500
    };

    try {
        console.log(1)
        const response = await fetch(apiUrl, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(requestBody)
        });

        if (!response.ok) {
            throw new Error(`HTTP error! Status: ${response.status}`);
        }

        const result = await response.json();
        console.log(result)
        document.getElementById('output-content').textContent = JSON.stringify(result, null, 4);
    } catch (error) {
        document.getElementById('output-content').textContent = `Error: ${error.message}`;
    }
});



// Close the dialog
document.getElementById("close-dialog").addEventListener("click", function () {
    const dialog = document.getElementById("output-dialog");
    dialog.close();
});
