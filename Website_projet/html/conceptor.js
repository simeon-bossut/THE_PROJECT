var gameSet = document.querySelector('#mainPlate');
var gameTab = [];
var viewSet = document.querySelector('#viewBox');



var tabDim = 4;

var obsTab = [];
var crateTab = [];

var lastCrateClicked;

for(let i = 0; i < tabDim * 4; i++) {
  obsTab.push(Math.floor(Math.random() * (tabDim)) + 1);
  //crateTab.push(Math.floor(Math.random() * (tabDim + 1)));
}

for(let i = 0; i < tabDim; i++) {
  crateTab.push([]);
  for(let j = 0; j < tabDim; j++) {
    crateTab[i].push({
      val: 0,
      hidden: false
    });
  }
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

    setView();

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


function exportGrid() {
  var exportTab = []; 

  for(let i = 0; i < tabDim; i++) {

  }
}


function initMainPlate() {

  gameTab = [];

  gameSet.innerHTML = "";

  gameSet.classList.remove("dim3","dim4","dim5");

  gameSet.classList.add("dim" + tabDim);

  for(let x = 0; x < tabDim + 2; x++) {
    gameTab.push([]);

    for(let y = 0; y < tabDim + 2; y++) {
      gameTab[x].push("empty");
    }
  }

  for(let y = 0; y < tabDim + 2; y++) {

    for(let x = 0; x < tabDim + 2; x++) {

      gameSet.innerHTML += `<div id="pos_${x - 1}_${y - 1}"></div>`
    
    }
  }




  for (let y = -1; y < tabDim + 1; y++) {

    for(let x = -1; x < tabDim + 1; x++) {
      // Observators
      if(x == -1 && y >= 0 && y < tabDim)
        insertElement(gameSet, x, y, `obs rotate270`);

      else if(y == -1 && x >= 0 && x < tabDim)
        insertElement(gameSet, x, y, `obs rotate00`);
      
      else if(x == tabDim && y >= 0 && y < tabDim)
        insertElement(gameSet, x, y, `obs rotate90`);

      else if(y == tabDim && x >= 0 && x < tabDim)
        insertElement(gameSet, x, y, `obs rotate180`);
      
      else if(x >= 0 && y >= 0 && y <= tabDim - 1 && x <= tabDim - 1)
        insertElement(gameSet, x, y, `cratePlace rotate00`);

      else
          insertElement(gameSet, x, y, `empty rotate00`);

    }

  }

  // OBSERVATORS DISPLAYING
  var count = 0;

  for(let i = 0; i < tabDim; i++) {
    let element = document.querySelector(`#pos_${i}_-1`);
    element.innerHTML += `<div id="obs_${count}" class="obsText rotate00">${obsTab[count]}</div>`;

    count++;
  }

  for(let i = 0; i < tabDim; i++) {
    let element = document.querySelector(`#pos_${tabDim}_${i}`);
    element.innerHTML += `<div id="obs_${count}" class="obsText rotate270">${obsTab[count]}</div>`;

    count++;
  }

  for(let i = tabDim - 1; i >= 0; i--) {
    let element = document.querySelector(`#pos_${i}_${tabDim}`);
    element.innerHTML += `<div id="obs-${count}" class="obsText rotate180">${obsTab[count]}</div>`;

    count++;
  }

  for(let i = tabDim - 1; i >= 0; i--) {
    let element = document.querySelector(`#pos_-1_${i}`);
    element.innerHTML += `<div id="obs-${count}" class="obsText rotate90">${obsTab[count]}</div>`;

    count++;
  }


}

initMainPlate();


const listKeys = ['KeyW', 'KeyA', 'KeyS', 'KeyD', 'ArrowLeft', 'ArrowUp', 'ArrowDown', 'ArrowRight', 'Space', 'Enter'];

window.addEventListener('keydown', e => {
  if (listKeys.includes(e.code))
    e.preventDefault();
})



function changeCrates(number) {
  let num = number.textContent;

  var x, y;

  if(lastCrateClicked.classList.contains('obsText')) {
    x = lastCrateClicked.parentElement.id.split('_')[1];
    y = lastCrateClicked.parentElement.id.split('_')[2];

    obsTab[Number(lastCrateClicked.id.split('_')[1])] = num == "" ? 0 : num;
    document.getElementById(lastCrateClicked.parentElement.id).childNodes[0].textContent = num;
  }
  else {
    x = lastCrateClicked.id.split('_')[1];
    y = lastCrateClicked.id.split('_')[2];

    crateTab[x][y].val = num == "" ? 0 : num;
  document.getElementById(lastCrateClicked.id).textContent = num;
  }

}

function hideCrate(hideButton) {
  let x = lastCrateClicked.id.split('_')[1];
  let y = lastCrateClicked.id.split('_')[2];

  if(hideButton.classList.contains("inv")) {
    crateTab[x][y].hidden = true;
    document.querySelector('#pos_' + x + '_' + y).classList.add('invCrate');
  }
  
  else {
    crateTab[x][y].hidden = false;
    document.querySelector('#pos_' + x + '_' + y).classList.remove('invCrate');
  }
  
}



document.querySelector('.crateInvChoice').addEventListener('click', e => {
  document.querySelector('.crateInvChoice').classList.toggle('inv');

  hideCrate(document.querySelector('.crateInvChoice'));
})

document.querySelectorAll('.cratePlace').forEach(elem => {
  elem.addEventListener('click', e => {
    let x = elem.id.split('_')[1];
    let y = elem.id.split('_')[2];

    if(crateTab[x][y].hidden == true)
      document.querySelector('.crateInvChoice').classList.add("inv"); 
    else
      document.querySelector('.crateInvChoice').classList.remove("inv");

    document.querySelector('#editTool').style.left = (elem.offsetLeft - document.querySelector('#editTool').offsetWidth / 2 + elem.offsetWidth / 2) + "px";
    document.querySelector('#editTool').style.top = (elem.offsetTop - document.querySelector('#editTool').offsetHeight / 2 - elem.offsetHeight + 19) + "px";
  
    if(lastCrateClicked != e.target || document.querySelector('#editTool').style.opacity == 0) {
      lastCrateClicked = e.target;

      document.querySelector('#editTool').style.opacity = 1;

      document.querySelector('#editTool').style.zIndex = 0;
    }

    else {
      document.querySelector('#editTool').style.opacity = document.querySelector('#editTool').style.opacity = 0;

      document.querySelector('#editTool').style.zIndex = -1;
    }
  })
})

document.querySelectorAll('.obsText').forEach((elem, index) => {
  elem.addEventListener('click', e => {
    let x = elem.parentElement.id.split('_')[1];
    let y = elem.parentElement.id.split('_')[2];

    console.log(elem.parentElement)

    if(obsTab[index].hidden == true)
      document.querySelector('.crateInvChoice').classList.add("inv"); 
    else
      document.querySelector('.crateInvChoice').classList.remove("inv");

    document.querySelector('#editTool').style.left = (elem.parentElement.offsetLeft - document.querySelector('#editTool').offsetWidth / 2 + elem.parentElement.offsetWidth / 2) + "px";
    document.querySelector('#editTool').style.top = (elem.parentElement.offsetTop - document.querySelector('#editTool').offsetHeight / 2 - elem.parentElement.offsetHeight + 19) + "px";
  
    if(lastCrateClicked != e.target || document.querySelector('#editTool').style.opacity == 0) {
      lastCrateClicked = e.target;

      document.querySelector('#editTool').style.opacity = 1;

      document.querySelector('#editTool').style.zIndex = 0;
    }

    else {
      document.querySelector('#editTool').style.opacity = document.querySelector('#editTool').style.opacity = 0;

      document.querySelector('#editTool').style.zIndex = -1;
    }
  })
})

document.addEventListener('click', e => {
  if(!e.target.classList.contains('cratePlace') && !e.target.classList.contains('obsText') && e.target.id != 'editTool' && !e.target.classList.contains('number') && !e.target.classList.contains('crateInvChoice')) {
    document.querySelector('#editTool').style.opacity = 0;

    document.querySelector('#editTool').style.zIndex = -1;
  }
})

window.onresize = (e) => {
  if(!lastCrateClicked) 
    return;
  
  document.querySelector('#editTool').style.left = (lastCrateClicked.offsetLeft - document.querySelector('#editTool').offsetWidth / 2 + lastCrateClicked.offsetWidth / 2) + "px";
  document.querySelector('#editTool').style.top = (lastCrateClicked.offsetTop - document.querySelector('#editTool').offsetHeight / 2 - lastCrateClicked.offsetHeight + 19) + "px";
}