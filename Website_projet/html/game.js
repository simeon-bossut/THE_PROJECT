var gameSet = document.querySelector('#mainPlate');
var gameTab = [];
var viewSet = document.querySelector('#view');



var tabDim = 3;

var obsTab = [];
var crateTab = [];

for(let i = 0; i < tabDim ** 2; i++) {
  obsTab.push(i);
  crateTab.push(i);
}





class Character {
  constructor(xPos, yPos, hatSkin, bodySkin) {
    this.x = xPos;
    this.y = yPos;

    this.hat = hatSkin || "default";
    this.body = bodySkin || "default";

    this.direction = "W";

    console.log("---", this.x, this.y, "---")

    document.querySelector(`#pos_${this.x}_${this.y}`).classList.toggle("hasPlayer");
    document.querySelector(`#pos_${this.x}_${this.y}`).innerHTML = `<div id="characterBox" class="rotate270">
                                                                      <div id="characterBody"></div>
                                                                      <div id="characterHat"></div>
                                                                      <div id="characterCrate"></div>
                                                                    </div>`;
  }

  drawChar() {

    var element = document.querySelector(`.hasPlayer`);

    let htmlCode = element.innerHTML;

    element.innerHTML = "";
    element.classList.toggle("hasPlayer");

    element = document.querySelector(`#pos_${this.x}_${this.y}`);

    let rotParent = Number(element.classList[1].split("tate")[1]);

    let rotation;
    
    if(this.direction == "W")
      rotation = (270 - rotParent) % 360 == 0 ? "00" : String(((720 + (270 - rotParent))) % 360); // 
    else if(this.direction == "N")
      rotation = (- rotParent) % 360 == 0 ? "00" : String((720 - rotParent) % 360);
    else if(this.direction == "E")
      rotation = (90 - rotParent) % 360 == 0 ? "00" : String(((720 + (90 - rotParent))) % 360)
    else if(this.direction == "S")
      rotation = (180 - rotParent) % 360 == 0 ? "00" : String(((720 + (180 - rotParent))) % 360)
    
    htmlCode = htmlCode.split('"');
    htmlCode[3] = "rotate" + rotation;
    htmlCode = htmlCode.join('"');

    element.innerHTML = htmlCode;
    element.classList.toggle("hasPlayer");

    return;
  }

  move(direction) {

    this.direction = direction;

    let x = this.x;
    let y = this.y;

    if(direction == "W") {
      if(gameTab[x] && (gameTab[x][y + 1] == "road")) {
        this.x--;
      }
    }

    else if(direction == "E") {
      if(gameTab[x] && (gameTab[x + 2][y + 1] == "road")) {
        this.x++;
      }
    }

    else if(direction == "N") {

      if(gameTab[x] && (gameTab[x + 1][y] == "road")) {
        this.y--;
      }
    }

    else if(direction == "S") {
      if(gameTab[x] && (gameTab[x + 1][y + 2] == "road")) {
        this.y++;
      }
    }

    this.drawChar();

    return;
  }
}


function insertElement(set, x, y, classList) {

  let elem = document.querySelector(`#pos_${x}_${y}`);

  elem.classList = [];

  classList.split(" ").forEach(classes => {
    elem.classList.add(classes);
  });
  
  let type = elem.classList;

  let name;

  if (type.contains("cornerRoad") || type.contains("straightRoad") || type.contains("TRoad") || type.contains("crossRoad"))
    name = "road";
  
  else if (type.contains("CStraight") || type.contains("CCorner"))
    name = "boxPick";
  
  else if (type.contains("crateArea"))
    name = "crateArea";
  
  else name = "empty";

  gameTab[x + 1][y + 1] = name;

}

function getElemByCoord(x, y) {

  var element = document.querySelector(`#pos_${x}_${y}`);

  return element;
}


function initMainPlate() {

  gameTab = [];

  gameSet.innerHTML = "";

  gameSet.classList.remove("dim3","dim4","dim5");

    gameSet.classList.add("dim" + tabDim);

  for(let x = 0; x <= tabDim * 2 + 4; x++) {
    gameTab.push([]);

    for(let y = 0; y <= tabDim * 2 + 2; y++) {
      gameTab[x].push("empty");
    }
  }

  for(let y = 0; y < tabDim * 2 + 3; y++) {

    for(let x = 0; x < tabDim * 2 + 2 + 3; x++) {

      gameSet.innerHTML += `<div id="pos_${x - 1}_${y - 1}"></div>`
    }
  }


  for (let y = -1; y < tabDim * 2 + 2; y++) {

    for(let x = -1; x < tabDim * 2 + 2 + 1; x++) {

      console.log(x, y);

      // Corner Road
      if(x == 0 && y == 0)
        insertElement(gameSet, x, y, `cornerRoad rotate00`);

        else if (x == tabDim * 2 && y == 0)
          insertElement(gameSet, x, y, `cornerRoad rotate90`);

        else if (x == 0 && y == tabDim * 2)
          insertElement(gameSet, x, y, `cornerRoad rotate270`);

        else if (x == tabDim * 2 && y == tabDim * 2 && y < tabDim * 2 + 1)
          insertElement(gameSet, x, y, `cornerRoad rotate180`);

        // Straight Road
        else if (x % 2 == 0 && y % 2 == 1 && x <= tabDim * 2 && y < tabDim * 2 + 1)
          insertElement(gameSet, x, y, `straightRoad rotate00`);

        else if (x % 2 == 1 && y % 2 == 0 && x <= tabDim * 2)
          insertElement(gameSet, x, y, `straightRoad rotate90`);

        // Intersection 3
        else if (x == 0 && y % 2 == 0 && x <= tabDim * 2)
          insertElement(gameSet, x, y, `TRoad rotate00`);

        else if (x == tabDim * 2 && y % 2 == 0 && x <= tabDim * 2)
          insertElement(gameSet, x, y, `TRoad rotate180`);

        else if (x % 2 == 0 && y == 0 && x <= tabDim * 2)
          insertElement(gameSet, x, y, `TRoad rotate90`);
      
        else if (x % 2 == 0 && y == tabDim * 2 && x <= tabDim * 2)
          insertElement(gameSet, x, y, `TRoad rotate270`);
      
        // Intersection 4
        else if (x % 2 == 0 && y % 2 == 0 && x > 0 && x < tabDim * 2 && y > 0 && y < tabDim * 2)
          insertElement(gameSet, x, y, `crossRoad rotate00`);
      
      // Observators
      else if((x == -1) && y % 2 == 1 && y > 0 && y <= tabDim * 2)
        insertElement(gameSet, x, y, `obs rotate270`);

      else if(y == -1 && x % 2 == 1 && x > 0 && x <= tabDim * 2)
        insertElement(gameSet, x, y, `obs rotate00`);
      
      else if(x == tabDim * 2 + 1 && y % 2 == 1 && y > 0 && y <= tabDim * 2)
        insertElement(gameSet, x, y, `obs rotate90`);

      else if(y == tabDim * 2 + 1 && x % 2 == 1 && x > 0 && x <= tabDim * 2)
        insertElement(gameSet, x, y, `obs rotate180`);
      
        else
          insertElement(gameSet, x, y, `empty rotate00`);

      }

    }

    if (tabDim == 3) {
      insertElement(gameSet, 6, 2, "crossRoad rotate00");
      insertElement(gameSet, 6, 4, "crossRoad rotate00");

      insertElement(gameSet, 7, 2, "straightRoad rotate90");
      insertElement(gameSet, 7, 4, "straightRoad rotate90");
    
      for (let i = 1; i < 6; i++) {
        switch (i) {
          case 1:
            insertElement(gameSet, 8, i, "cornerRoad rotate00");
            break;
          case 2: case 4:
            insertElement(gameSet, 8, i, "crossRoad rotate00");
            break;
          case 3:
            insertElement(gameSet, 8, i, "TRoad rotate00");
            break;
          case 5:
            insertElement(gameSet, 8, i, "cornerRoad rotate270");
            break;
        
        }

        switch (i) {
          case 1:
            insertElement(gameSet, 9, i, "CCorner rotate00");
            break;
          case 2: case 3: case 4:
            insertElement(gameSet, 9, i, "CStraight rotate00");
            break;
          case 5:
            insertElement(gameSet, 9, i, "CCorner rotate90");
            break;
        }
      }
    }

  else if(tabDim == 4) {
    insertElement(gameSet, 8, 4, "crossRoad rotate00");
    insertElement(gameSet, 9, 4, "straightRoad rotate90");

    insertElement(gameSet, 10, 2, "cornerRoad rotate00");
    insertElement(gameSet, 10, 3, "TRoad rotate00");
    insertElement(gameSet, 10, 4, "crossRoad rotate00");
    insertElement(gameSet, 10, 5, "TRoad rotate00");
    insertElement(gameSet, 10, 6, "cornerRoad rotate270");

    insertElement(gameSet, 11, 2, "CCorner rotate00");
    insertElement(gameSet, 11, 3, "CStraight rotate00");
    insertElement(gameSet, 11, 4, "CStraight rotate00");
    insertElement(gameSet, 11, 5, "CStraight rotate00");
    insertElement(gameSet, 11, 6, "CCorner rotate90");
  }

}

const listKeys = ['KeyW', 'KeyA', 'KeyS', 'KeyD', 'ArrowLeft', 'ArrowUp', 'ArrowDown', 'ArrowRight', 'Space', 'Enter'];

  window.addEventListener('keydown', e => {
    if (listKeys.includes(e.code))
      e.preventDefault();
  })



  document.addEventListener('keydown', e => {
    let key = e.code;

    if (key == "KeyA" || key == "ArrowLeft") {
      player.move("W");
    }
    else if (key == "KeyD" || key == "ArrowRight") {
      player.move("E");
    }
    else if (key == "KeyS" || key == "ArrowDown") {
      player.move("S");
    }
    else if (key == "KeyW" || key == "ArrowUp") {
      player.move("N");
    }
  })

  
initMainPlate();

var player;

if(tabDim == 3) {
  player = new Character(8, 3);
}

else if(tabDim == 4) {
  player = new Character(10, 4);
}
  
function initView() {

  viewSet.innerHTML = "";

  tabDim = 3;

  for (let y = 1; y < tabDim*2; y+=2) {
    for (let x = 1; x < tabDim * 2; x += 2) {
      getElemByCoord(x, y).innerHTML = x * y;
      max = parseInt(getElemByCoord(x, y).textContent);
    }
  } 
  
}

initView();