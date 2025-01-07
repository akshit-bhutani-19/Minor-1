document.getElementById('submitForm').addEventListener('click', async function (event) {
    event.preventDefault(); // Prevent form submission

    // Gather form data
    const ndvi = parseFloat(document.getElementById("ndvi").value);
    const nightlight = parseFloat(document.getElementById("nightlight").value);
    const area = parseFloat(document.getElementById("area").value);
    const chital = parseFloat(document.getElementById("chital").value);
    const sambar = parseFloat(document.getElementById("sambar").value);
    const barkingDeer = parseFloat(document.getElementById("barkingDeer").value);
    const wildpig = parseFloat(document.getElementById("wildPig").value);
    const elephant = parseFloat(document.getElementById("elephant").value);
    const nilgai = parseFloat(document.getElementById("nilgai").value);
    const langur = parseFloat(document.getElementById("langur").value);
    const hogDeer = parseFloat(document.getElementById("hogDeer").value);
    const chinkara = parseFloat(document.getElementById("chinkara").value);
    const boar = parseFloat(document.getElementById("boar").value);

    // Validate input ranges
    if (isNaN(ndvi) || ndvi < 0 || ndvi > 10000) {
        alert("NDVI must be a number between 0 and 10000.");
        return;
    }
    if (isNaN(nightlight) || nightlight < 0 || nightlight > 10) {
        alert("Nightlight must be a number between 0 and 10.");
        return;
    }
    if (isNaN(area) || area <= 0) {
        alert("Area must be a positive number.");
        return;
    }

    // Prey weights
    const preyWeights = {
        chital: 80,
        sambar: 180,
        barkingDeer: 18,
        wildpig: 80,
        elephant: 1000,
        nilgai: 160,
        langur: 1,
        hogDeer: 100,
        chinkara: 23,
        boar: 180
    };

    const totalPreyDensity =
        ((chital * preyWeights.chital) +
        (sambar * preyWeights.sambar) +
        (barkingDeer * preyWeights.barkingDeer) +
        (wildpig * preyWeights.wildpig) +
        (elephant * preyWeights.elephant) +
        (nilgai * preyWeights.nilgai) +
        (langur * preyWeights.langur) +
        (hogDeer * preyWeights.hogDeer) +
        (chinkara * preyWeights.chinkara) +
        (boar * preyWeights.boar)) / 10000;

    const normalizedNDVI = ndvi / 10000;

    // Predict tiger density
    const tigerDensity = -0.0871 + (0.0565 * totalPreyDensity) + (0.2822 * normalizedNDVI) + (-0.1252 * nightlight);

    // Calculate total tiger population
    const totalPopulation = tigerDensity * area;

    // Display the result
    let resultText;
    if (tigerDensity <= 0) {
        resultText = 'Tigers are not possible in this area.';
    } else {
        resultText = `Predicted Tiger Density: ${tigerDensity.toFixed(3)} per sq.km<br>
                      Total Tiger Population: ${totalPopulation.toFixed(0)}`;
    }

    // Update and show the dialog
    const dialog = document.getElementById("output-dialog");
    document.getElementById("output-content").innerHTML = resultText;

    if (typeof dialog.showModal === "function") {
        dialog.showModal(); // Open the dialog
    } else {
        alert("Dialog is not supported in your browser. Showing result in alert instead.");
        alert(resultText);
    }

    // Close the dialog
    document.getElementById("close-dialog").addEventListener("click", function () {
        dialog.close();
    });
});
