var gameSet = document.querySelector('#mainPlate');
var gameTab = [];
var viewSet = document.querySelector('#view');



var tabDim = 3;

var obsTab = [];
var crateTab = [];

for(let i = 0; i < tabDim * 4; i++) {
  obsTab.push(Math.floor(Math.random() * (tabDim + 1)));
  crateTab.push(Math.floor(Math.random() * (tabDim + 1)));
}





class Character {
  constructor(xPos, yPos, hatSkin, bodySkin) {
    this.x = xPos;
    this.y = yPos;

    this.hat = hatSkin || "default";
    this.body = bodySkin || "default";

    this.direction = "W";

    this.numCrate = 0;


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
      rotation = (270 - rotParent) % 360 == 0 ? "00" : String(((720 + (270 - rotParent))) % 360);
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
  
  else if (type.contains("cratePlace"))
    name = "cratePlace";
  
  else if (type.contains("Trash"))
    name = "trash";
  
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
      
      else if(x > 0 && x < tabDim * 2 && y > 0 && y < tabDim * 2 && x % 2 == 1 && y % 2 == 1)
        insertElement(gameSet, x, y, `cratePlace rotate00`);
      else
          insertElement(gameSet, x, y, `empty rotate00`);

    }

  }

  insertElement(gameSet, 0, -1, "Trash rotate00");
  insertElement(gameSet, 0, tabDim * 2 + 1, "Trash rotate00");

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


  // OBSERVATORS DISPLAYING
  var count = 0;

  for(let i = 0; i < tabDim; i++) {
    let element = document.querySelector(`#pos_${i * 2 + 1}_-1`);
    element.innerHTML += `<div class="obsText rotate00">${obsTab[count]}</div>`;

    count++;
  }

  for(let i = 0; i < tabDim; i++) {
    let element = document.querySelector(`#pos_${tabDim * 2 + 1}_${i * 2 + 1}`);
    element.innerHTML += `<div class="obsText rotate270">${obsTab[count]}</div>`;

    count++;
  }

  for(let i = tabDim - 1; i >= 0; i--) {
    let element = document.querySelector(`#pos_${i * 2 + 1}_${tabDim * 2 + 1}`);
    element.innerHTML += `<div class="obsText rotate180">${obsTab[count]}</div>`;

    count++;
  }

  for(let i = tabDim - 1; i >= 0; i--) {
    let element = document.querySelector(`#pos_-1_${i * 2 + 1}`);
    element.innerHTML += `<div class="obsText rotate90">${obsTab[count]}</div>`;

    count++;
  }


  // CRATES DISPLAYING

  document.querySelectorAll(".cratePlace").forEach((element, index) => {
    if(crateTab[index] != 0)
      element.innerHTML = crateTab[index];
  })


}


function crateGrab() {
  let xAdd = 0;
  let yAdd = 0;

  if(player.direction == "E")
    xAdd++;
  else if(player.direction == "W")
    xAdd--;
  else if(player.direction == "N")
    yAdd--;
  else if(player.direction == "S")
    yAdd++;

  if(gameTab[player.x + 1 + xAdd][player.y + 1 + yAdd] == "cratePlace") {
    let crateArea = document.querySelector(`#pos_${player.x + xAdd}_${player.y + yAdd}`);

    let qty =  Number(crateArea.textContent);


    // Pick a box
    if(player.numCrate < tabDim && qty > 0) {
      player.numCrate++;
      qty--;
    }

    if(qty == 0) qty = "";

    crateArea.textContent = qty;
  }

  // Facing a pick area
  else if(gameTab[player.x + 1 + xAdd][player.y + 1 + yAdd] == "boxPick") {

    if(player.numCrate == tabDim)
      return;
    
    player.numCrate++;  
  }


  // Draw Player Crate number
  let num = player.numCrate;

  if(num == 0)
    num = "";
    
  document.querySelector("#characterCrate").innerHTML = num;

}


function crateDrop() {
  let xAdd = 0;
  let yAdd = 0;

  if(player.direction == "E")
    xAdd++;
  else if(player.direction == "W")
    xAdd--;
  else if(player.direction == "N")
    yAdd--;
  else if(player.direction == "S")
    yAdd++;

  if(gameTab[player.x + 1 + xAdd][player.y + 1 + yAdd] == "cratePlace") {
    let crateArea = document.querySelector(`#pos_${player.x + xAdd}_${player.y + yAdd}`);

    let qty =  Number(crateArea.textContent);

    // Place a box on stack
    if(player.numCrate > 0 && qty < tabDim) {
      player.numCrate--;
      qty++;
    }

    if(qty == 0) qty = "";

    crateArea.textContent = qty;
  }

  // Facing a trash
  else if(gameTab[player.x + 1 + xAdd][player.y + 1 + yAdd] == "trash") {

    if(player.numCrate > 0)
      player.numCrate--;
  }


  // Draw Player Crate number
  let num = player.numCrate;

  if(num == 0)
    num = "";
    
  document.querySelector("#characterCrate").innerHTML = num;
}




const listKeys = ['KeyW', 'KeyA', 'KeyS', 'KeyD', 'ArrowLeft', 'ArrowUp', 'ArrowDown', 'ArrowRight', 'Space', 'Enter'];

window.addEventListener('keydown', e => {
  if (listKeys.includes(e.code))
    e.preventDefault();
})



document.addEventListener('keydown', e => {
  let key = e.code;

  // Movements Player
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

  // POV Player
  else if (key == "KeyP") {
    setView();
  }

  // Crates actions
  else if(key == "Space") {
    crateGrab();
  }
  else if(key == "Enter") {
    crateDrop();
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
  
function setView() {

  let view = document.querySelectorAll('[id^="crate"]');

  for (let i = 0; i < view.length; i++) 
    view[i].remove();
  
  tabDim = 3;
  
  let arr = [];

  if (player.x % 2 == 1 && player.x < 7) {

    if (player.direction == 'N' && player.y > 0) {

      max = getElemByCoord(player.x, player.y - 1).innerHTML;
      arr = [max];
      for (let y = player.y - 1; y > 0; y -= 2) {

        if (getElemByCoord(player.x, y).innerHTML > max) {
          max = getElemByCoord(player.x, y).innerHTML;
          arr.push(max);
        }
      }
    }

    if (player.direction == 'S'&& player.y < 6) {

      max = getElemByCoord(player.x, player.y + 1).innerHTML;
      arr = [max];
      for (let y = player.y + 1; y < tabDim * 2; y += 2) {

        if (getElemByCoord(player.x, y).innerHTML > max) {
          max = getElemByCoord(player.x, y).innerHTML;
          arr.push(max);
        }
      }
    }
  }

  if (player.y % 2 == 1 && player.x < 7) {
    
    if (player.direction == 'E' && player.x < 6) {
      max = getElemByCoord(player.x+1, player.y).innerHTML;
      arr = [max];
      for (let x = player.x+1; x < tabDim * 2; x += 2) {
        
        if(getElemByCoord(x, player.y).innerHTML > max){
          max = getElemByCoord(x, player.y).innerHTML;
          arr.push(max);
        }
      }
    }

    if (player.direction == 'W'&& player.x > 0) {
      max = getElemByCoord(player.x-1, player.y).innerHTML;
      arr = [max];
      for (let x = player.x - 1; x > 0; x -= 2) {
        
        if (getElemByCoord(x, player.y).innerHTML > max) {
          max = getElemByCoord(x, player.y).innerHTML;
          arr.push(max);
        }
      }
    }
  }
  for (let i = 0; i < arr.length; i++){
    viewSet.innerHTML += `<div id = "crate${arr[i]}" style = "position:absolute; z-index:${arr.length - i};"}></div>`;
  }
}