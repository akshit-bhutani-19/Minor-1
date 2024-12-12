// script.js

document.getElementById("analyse-btn").addEventListener("click", function () {
    // Gather form data
    const ndvi = document.getElementById("ndvi").value;
    const nightlight = document.getElementById("nightlight").value;
    const area = document.getElementById("area").value;
    const chital = document.getElementById("chital").value;
    const sambar = document.getElementById("sambar").value;
    const barkingDeer = document.getElementById("barking-deer").value;

    // Prepare the output content
    const output = `
        <p>NDVI: ${ndvi}</p>
        <p>Nightlight: ${nightlight}</p>
        <p>Area (sq km): ${area}</p>
        <p>Prey Density:</p>
        <ul>
            <li>Chital: ${chital}</li>
            <li>Sambar: ${sambar}</li>
            <li>Barking Deer: ${barkingDeer}</li>
        </ul>
    `;

    // Display output in the dialog box
    const outputContent = document.getElementById("output-content");
    outputContent.innerHTML = output;

    const dialog = document.getElementById("output-dialog");
    dialog.showModal();
});

// Close the dialog
document.getElementById("close-dialog").addEventListener("click", function () {
    const dialog = document.getElementById("output-dialog");
    dialog.close();
});
