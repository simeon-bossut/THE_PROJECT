<script>

var player;

var gameSet = document.querySelector('#mainPlate');
var gameTab = [];
var viewSet = document.querySelector('#povBoxContent');


var timeStart = null;
var newGrid = false;


var tabDim = document.querySelector('select[name="size"]').value;

var obsTab;
var crateTab; // = [4, 1, 3, 2, 1, 2, 4, 3, 2, 3, 1, 4, 3, 4, 2, 0];





class Character {
  constructor(xPos, yPos, hatSkin, bodySkin) {
    this.x = xPos;
    this.y = yPos;

    this.hat  = "<?php if(isset($resHat)) { echo $resHat; } else { echo 'default'; } ?>";
    this.body = "<?php if(isset($resBody)) { echo $resBody; } ?>";

    this.direction = "W";

    this.numCrate = 0;


    document.querySelector(`#pos_${this.x}_${this.y}`).classList.toggle("hasPlayer");
    document.querySelector(`#pos_${this.x}_${this.y}`).innerHTML = `<div id="characterBox" class="rotate270">
                                                                      <div id="characterBody"></div>
                                                                      <div id="characterHat"></div>
                                                                      <div id="characterCrate"></div>
                                                                    </div>`;
    
    if(this.hat != 'default') {
      document.querySelector("#characterHat").style.backgroundImage = 'url("../Images/customizations/' + this.hat + '.svg")';
      document.querySelector("#characterHatIcon").style.backgroundImage = 'url("../Images/customizations/' + this.hat + '.svg")';
    } else {
      document.querySelector("#characterHat").style.backgroundImage = 'none';
      document.querySelector("#characterHatIcon").style.backgroundImage = 'none';
    }      

    document.querySelector("#characterBody").style.backgroundImage = 'url("../Images/customizations/' + this.body + '.svg")';
    document.querySelector("#characterBodyIcon").style.backgroundImage = 'url("../Images/customizations/' + this.body + '.svg")';
    
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

    if(newGrid == true) {
      timeStart = new Date().getTime();
      newGrid = false;
    }


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

    setView();

    return;
  }
}


function checkVictory() {

  if(timeStart == null)
    return false;

  if(crateTab.includes(0))
    return false;

  for(let i = 0; i < tabDim; i++) {

    let lastVal1 = [];
    let lastVal2 = [];

    for(let j = 0; j < tabDim; j++) {
      if(!lastVal1.includes(crateTab[i * tabDim + j])) {
        lastVal1.push(crateTab[i * tabDim + j]);
      }
      else {
        return false;
      }
      
      if(!lastVal2.includes(crateTab[j * tabDim + i])) {
        lastVal2.push(crateTab[j * tabDim + i]);
      }
      else {
        return false;
      }

    }  

    let maxVal1 = -1;
    let nbStack1 = 0;

    let maxVal2 = -1;
    let nbStack2 = 0;

    for(let k = 0; k < tabDim; k++) {
      if(lastVal1[k] > maxVal1) {
        nbStack1++;
        maxVal1 = lastVal1[k];
      }

      if(lastVal2[k] > maxVal2) {
        nbStack2++;
        maxVal2 = lastVal2[k];
      }
    }

    if(obsTab[i] != nbStack2) {
      return false;
    }

    if(obsTab[tabDim*4 - 1 - i] != nbStack1) {
      return false;
    }
  }

  for(let i = 0; i < tabDim; i++) {

    let lastVal1 = [];
    let lastVal2 = [];

    for(let j = 0; j < tabDim; j++) {
      if(!lastVal1.includes(crateTab[i * tabDim + j])) {
        lastVal1.push(crateTab[i * tabDim + j]);
      }
      else {
        return false;
      }
      
      if(!lastVal2.includes(crateTab[j * tabDim + i])) {
        lastVal2.push(crateTab[j * tabDim + i]);
      }
      else {
        return false;
      }
    }

    let maxVal1 = -1;
    let nbStack1 = 0;

    let maxVal2 = -1;
    let nbStack2 = 0;

    lastVal1.reverse();
    lastVal2.reverse();

    for(let k = 0; k < tabDim; k++) {
      if(lastVal1[k] > maxVal1) {
        nbStack1++;
        maxVal1 = lastVal1[k];
      }

      if(lastVal2[k] > maxVal2) {
        nbStack2++;
        maxVal2 = lastVal2[k];
      }
    }

    if(obsTab[i + tabDim] != nbStack1) {
      return false;
    }

    if(obsTab[tabDim*4 - 1 - tabDim - i] != nbStack2) {
      return false;
    }
  }

  
  // All conditions passed


  document.querySelector(".victoryScreen").classList.add('opened');

  totalTime = new Date(new Date().getTime() - timeStart);

  let min = Math.floor(totalTime.getTime() / 1000 / 60);
  min = min < 10 ? '0' + min : min;

  let sec = Math.floor(totalTime.getTime() / 1000 % 60);
  sec = sec < 10 ? '0' + sec : sec; 

  document.querySelector("#timerVictory span").textContent = min + ':' + sec;

  timeStart = null;

  return true;
}


/// Display a clue on grid
function revealClue() {

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

document.querySelector('#close-popup').onclick = () => {
  document.querySelector('.popup').classList.remove('displayed');
}

function initMainPlate() {

  newGrid = true;
  timeStart = null;

  crateTab = [];

  tabDim = Number(document.querySelector('select[name="size"]').value);

  for(let i = 0; i < tabDim ** 2; i++) {
    crateTab.push(0);
  }

  document.querySelector(".victoryScreen").classList.remove('opened');

  // A CHANGER
  if(tabDim == 3) {
    obsTab = [2, 2, 1, 1, 2, 2, 3, 1, 2, 2, 1, 3];
    crateTab = [1, 0, 3, 3, 1, 2, 2, 3, 0];
  }

  if(tabDim == 4) {
    obsTab = [1, 4, 2, 3, 3, 2, 1, 3, 2, 2, 1, 2, 2, 3, 3, 1];
  }

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

  insertElement(gameSet, tabDim*2 + 1 + 2, -1, "clueButton rotate00");
  insertElement(gameSet, tabDim*2 + 1 + 1, -1, "keysButton rotate00");


  document.querySelector('.clueButton').onclick = () => {
    revealClue();
  }

  document.querySelector('.keysButton').onclick = () => {
    document.querySelector('.popup').classList.toggle('displayed');
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
    if(crateTab[index] != 0) {
      element.innerHTML = crateTab[index];
      element.classList.add('crateLocked');
    }
  })

  if(tabDim == 3) {
    player = new Character(8, 3);
  }

  else if(tabDim == 4) {
    player = new Character(10, 4);
  }

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

    if(crateArea.classList.contains('crateLocked'))
      return;

    let qty =  Number(crateArea.textContent);


    // Pick a box
    if(player.numCrate <= tabDim && qty > 0) {
      player.numCrate++;
      qty--;

      crateTab[Math.floor((player.x + xAdd) / 2) + (Math.floor((player.y + yAdd) / 2) * tabDim)] = qty;

      //console.log(Math.floor((player.x + xAdd) / 2) + (Math.floor((player.y + yAdd) / 2) * tabDim), Math.floor((player.x + xAdd) / 2), Math.floor((player.y + yAdd) / 2));
    }

    if(qty == 0) qty = "";

    crateArea.textContent = qty;
  }

  // Facing a pick area
  else if(gameTab[player.x + 1 + xAdd][player.y + 1 + yAdd] == "boxPick") {

    if(player.numCrate > tabDim)
      return;
    
    player.numCrate++;  
  }


  // Draw Player Crate number
  let num = player.numCrate;

  if(num == 0)
    num = "";
    
  document.querySelector("#characterCrate").innerHTML = num;

  checkVictory();


  setView();
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

    if(crateArea.classList.contains('crateLocked'))
      return;

    let qty =  Number(crateArea.textContent);

    // Place a box on stack
    if(player.numCrate > 0 && qty < tabDim) {
      player.numCrate--;
      qty++;

      crateTab[Math.floor((player.x + xAdd) / 2) + (Math.floor((player.y + yAdd) / 2) * tabDim)] = qty;
    }

    if(qty == 0) qty = "";

    crateArea.textContent = qty;
  }

  // Facing a trash
  else if(gameTab[player.x + 1 + xAdd][player.y + 1 + yAdd] == "trash" || gameTab[player.x + 1 + xAdd][player.y + 1 + yAdd] == "boxPick") {

    if(player.numCrate > 0)
      player.numCrate--;
  }


  // Draw Player Crate number
  let num = player.numCrate;

  if(num == 0)
    num = "";
    
  document.querySelector("#characterCrate").innerHTML = num;

  checkVictory();

  setView();
}




const listKeys = ['KeyW', 'KeyA', 'KeyS', 'KeyD', 'ArrowLeft', 'ArrowUp', 'ArrowDown', 'ArrowRight', 'Space', 'Semicolon', 'KeyL'];

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
  /*else if (key == "KeyP") {
    setView();
  }*/

  // Crates actions
  else if(key == "KeyL") {
    crateGrab();
  }
  else if(key == "Semicolon") {
    crateDrop();
  }
})

  
initMainPlate();
  
function setView() {

  let view = document.querySelectorAll('div[id^="crate"]');

  for (let i = 0; i < view.length; i++) 
    view[i].remove();
  
  let arr = [];

  if (player.x % 2 == 1 && player.x < tabDim * 2 + 1) {

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

    if (player.direction == 'S'&& player.y < tabDim * 2) {

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

  if (player.y % 2 == 1 && player.x < tabDim * 2 + 1) {
    
    if (player.direction == 'E' && player.x < tabDim * 2) {
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
    viewSet.innerHTML += `<div id = "crate${arr[i]}"></div>`;
  }
}

</script>