document.getElementById('submitForm').addEventListener('click', async function (event) {
        event.preventDefault(); // Prevent form from submitting normally

        // Gather form data
        var ndvi = document.getElementById("ndvi").value;
        const nightlight = document.getElementById("nightlight").value;
        const area = document.getElementById("area").value;
        const chital = document.getElementById("chital").value;
        const sambar = document.getElementById("sambar").value;
        const barkingDeer = document.getElementById("barkingDeer").value;
        const wildpig = document.getElementById("wildPig").value;
        const elephant = document.getElementById("elephant").value;
        const nilgai = document.getElementById("nilgai").value;
        const langur = document.getElementById("langur").value;
        const hogDeer = document.getElementById("hogDeer").value;
        const chinkara = document.getElementById("chinkara").value;
        const boar = document.getElementById("boar").value;

        // Validation for input ranges
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
        if (isNaN(chital) || chital < 0) {
            alert("Chital count must be a non-negative number.");
            return;
        }
        if (isNaN(sambar) || sambar < 0) {
            alert("Sambar count must be a non-negative number.");
            return;
        }
        if (isNaN(barkingDeer) || barkingDeer < 0) {
            alert("Barking Deer count must be a non-negative number.");
            return;
        }
        if (isNaN(wildpig) || wildpig < 0) {
            alert("Wild Pig count must be a non-negative number.");
            return;
        }
        if (isNaN(elephant) || elephant < 0) {
            alert("Elephant count must be a non-negative number.");
            return;
        }
        if (isNaN(nilgai) || nilgai < 0) {
            alert("Nilgai count must be a non-negative number.");
            return;
        }
        if (isNaN(langur) || langur < 0) {
            alert("Langur count must be a non-negative number.");
            return;
        }
        if (isNaN(hogDeer) || hogDeer < 0) {
            alert("Hog Deer count must be a non-negative number.");
            return;
        }
        if (isNaN(chinkara) || chinkara < 0) {
            alert("Chinkara count must be a non-negative number.");
            return;
        }
        if (isNaN(boar) || boar < 0) {
            alert("Boar count must be a non-negative number.");
            return;
        }

        const preyWeights = {
            chital: 80,    // Example: weights for each species
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
            (boar * preyWeights.boar)) / 1000;

        ndvi = ndvi / 1000;

        // Predict tiger density (a simple function, you can modify based on actual regression coefficients)
        const tigerDensity = -0.0871 + (0.0565 * totalPreyDensity) + (0.2822 * ndvi) + (-0.1252 * nightlight);

        // Calculate total tiger population (density * area)
        const totalPopulation = tigerDensity * area;

        // Display the result
        if (tigerDensity <= 0) {
            resultText = 'Tigers not possible in this area';  // If density is <= 0
        } else {
            resultText = `Predicted Tiger Density: ${tigerDensity.toFixed(3)} per sq.km<br>
                          Total Tiger Population: ${totalPopulation.toFixed(0)}`;
        }
        

        document.getElementById("output-content").innerHTML = resultText;

        console.log(resultText);

        // Close the dialog
        document.getElementById("close-dialog").addEventListener("click", function () {
            const dialog = document.getElementById("output-dialog");
            dialog.close();
        });
    });
