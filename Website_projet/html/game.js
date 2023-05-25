var gameSet = document.querySelector('#mainPlate');

function insertElement(set, element) {

  set.innerHTML += element;

}

function getElemByCoord(x, y) {

  var element = document.querySelector(`#pos_${x}_${y}`);

  return element;
}

function initCharacter() {

}


function initMainPlate() {

  gameSet.innerHTML = "";

  let tabDim = 3;

  gameSet.classList.remove("dim3","dim4","dim5");

  gameSet.classList.add("dim" + tabDim);


  for(let y = -1; y < tabDim * 2 + 2; y++) {

    for(let x = -1; x < tabDim * 2 + 1 + 3; x++) {

      if(x == 0 && y == 0)
        insertElement(gameSet, `<div class="cornerRoad rotate00" id="pos_${x}_${y}">
          <div id="characterBox">
            <div id="characterBody"></div>
            <div id="characterHat"></div>
            <div id="characterCrate"></div>
          </div>
        </div>`);

      else if(x == tabDim * 2 && y == 0)
        insertElement(gameSet, `<div class="cornerRoad rotate90" id="pos_${x}_${y}"></div>`);

      else if(x == 0 && y == tabDim * 2)
        insertElement(gameSet, `<div class="cornerRoad rotate270" id="pos_${x}_${y}"></div>`);

      else if(x == tabDim * 2 && y == tabDim * 2 && y < tabDim * 2 + 1)
        insertElement(gameSet, `<div class="cornerRoad rotate180" id="pos_${x}_${y}"></div>`);

      else if(x % 2 == 0 && y % 2 == 1 && x <= tabDim * 2 && y < tabDim * 2 + 1)
        insertElement(gameSet, `<div class="straightRoad rotate00" id="pos_${x}_${y}"></div>`);

      else if(x % 2 == 1 && y % 2 == 0 && x <= tabDim * 2)
        insertElement(gameSet, `<div class="straightRoad rotate90" id="pos_${x}_${y}"></div>`);

      else if(x == 0 && y % 2 == 0 && x <= tabDim * 2)
        insertElement(gameSet, `<div class="TRoad rotate00" id="pos_${x}_${y}"></div>`);

      else if(x == tabDim * 2 && y % 2 == 0 && x <= tabDim * 2)
        insertElement(gameSet, `<div class="TRoad rotate180" id="pos_${x}_${y}"></div>`);

      else if(x % 2 == 0 && y == 0 && x <= tabDim * 2)
        insertElement(gameSet, `<div class="TRoad rotate90" id="pos_${x}_${y}"></div>`);
      
      else if(x % 2 == 0 && y == tabDim * 2 && x <= tabDim * 2)
        insertElement(gameSet, `<div class="TRoad rotate270" id="pos_${x}_${y}"></div>`);
      
      else if(x % 2 == 0 && y % 2 == 0 && x > 0 && x < tabDim * 2 && y > 0 && y < tabDim * 2)
        insertElement(gameSet, `<div class="crossRoad rotate00" id="pos_${x}_${y}"></div>`);
      
      else
        insertElement(gameSet, `<div id="pos_${x}_${y}"></div>`)

    }

  }

  if (tabDim == 3) {
    getElemByCoord(6, 2).classList.add("crossRoad", "rotate00");
    getElemByCoord(6, 2).classList.remove("TRoad", "rotate180");
    getElemByCoord(6, 4).classList.add("crossRoad", "rotate00");
    getElemByCoord(6, 4).classList.remove("TRoad", "rotate180");


    getElemByCoord(7, 2).classList.add("straightRoad", "rotate90");
    getElemByCoord(7, 4).classList.add("straightRoad", "rotate90");
    
    for (let i = 1; i < 6; i++) {

      switch (i) {
        case 1:
          getElemByCoord(8, i).classList.add("cornerRoad", "rotate00");
          break;
        case 2: case 4:
          getElemByCoord(8, i).classList.add("crossRoad", "rotate00");
          break;
        case 3:
          getElemByCoord(8, i).classList.add("TRoad", "rotate00");
          break;
        case 5:
          getElemByCoord(8, i).classList.add("cornerRoad", "rotate270");
          break;
        
      }

      switch (i) {
        case 1:
          getElemByCoord(9, i).classList.add("CCorner", "rotate00");
          break;
        case 2: case 3: case 4:
          getElemByCoord(9, i).classList.add("CStraight", "rotate00");
          break;
        case 5:
          getElemByCoord(9, i).classList.add("CCorner", "rotate90");
          break;
      }
    }
  }

}

initMainPlate();