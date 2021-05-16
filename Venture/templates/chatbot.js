document.addEventListener("DOMContentLoaded", () => {
    document.querySelector("#input").addEventListener("keydown", function(e) {
      if (e.code === "Enter") {
        let input = inputField.value;
        inputField.value = "";
        output(input);
        //   console.log("You clicked the form and pressed the enter button!")
      }
    });
  });