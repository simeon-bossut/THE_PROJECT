var gameSet = document.querySelector('#mainPlate');


function insertElement(set, element) {

  set.innerHTML += element;

}


function initMainPlate() {

  gameSet.innerHTML = "";

  let tabDim = 3;

  gameSet.classList.remove("dim3");
  gameSet.classList.remove("dim4");
  gameSet.classList.remove("dim5");

  gameSet.classList.add("dim" + tabDim);


  for(let y = -1; y < tabDim * 2 + 2; y++) {

    for(let x = -1; x < tabDim * 2 + 1 + 3; x++) {

      console.log(x % 2 == 0, y);

      if(x == 0 && y == 0)
        insertElement(gameSet, `<div class="cornerRoad rotate00"></div>`);

      else if(x == tabDim * 2 && y == 0)
        insertElement(gameSet, `<div class="cornerRoad rotate90"></div>`);

      else if(x == 0 && y == tabDim * 2)
        insertElement(gameSet, `<div class="cornerRoad rotate270"></div>`);

      else if(x == tabDim * 2 && y == tabDim * 2 && y < tabDim * 2 + 1)
        insertElement(gameSet, `<div class="cornerRoad rotate180"></div>`);

      else if(x % 2 == 0 && y % 2 == 1 && x <= tabDim * 2 && y < tabDim * 2 + 1)
        insertElement(gameSet, `<div class="straightRoad rotate00"></div>`);

      else if(x % 2 == 1 && y % 2 == 0 && x <= tabDim * 2)
        insertElement(gameSet, `<div class="straightRoad rotate90"></div>`);

      else if(x == 0 && y % 2 == 0 && x <= tabDim * 2)
        insertElement(gameSet, `<div class="TRoad rotate00"></div>`);

      else if(x == tabDim * 2 && y % 2 == 0 && x <= tabDim * 2)
        insertElement(gameSet, `<div class="TRoad rotate180"></div>`);

      else if(x % 2 == 0 && y == 0 && x <= tabDim * 2)
        insertElement(gameSet, `<div class="TRoad rotate90"></div>`);
      
      else if(x % 2 == 0 && y == tabDim * 2 && x <= tabDim * 2)
        insertElement(gameSet, `<div class="TRoad rotate270"></div>`);
      
      else if(x % 2 == 0 && y % 2 == 0 && x > 0 && x < tabDim * 2 && y > 0 && y < tabDim * 2)
        insertElement(gameSet, `<div class="crossRoad rotate00"></div>`);
      
      else
        insertElement(gameSet, `<div class="emptyYet"></div>`)

    }

  }

}
 
initMainPlate();