var gameSet = document.querySelector('#mainPlate');
var viewSet = document.querySelector('#viewBox');



var tabDim = 4;
document.cookie = "tabDim="+tabDim; 

var obsTab = [];
var crateTab = [];

var lastCrateClicked;

function getElemByCoord(x, y) {

  var element = document.querySelector(`#pos_${x}_${y}`);
 
  return element;
}

function createStringGrid(dim, obs, crates) {

  var string = "";

  for(let i = 0; i < dim*4; i++) {
    let obss = document.querySelector("#obs_" + i);
    let value = obss.textContent;
    if(value == "" || obss.parentElement.classList.contains("invCrate"))
      value = "0";
    string += value == "" ? "0" : value;
  }


  crates.forEach(crate => {
    let value = crate.textContent;
    if(value == "" || crate.classList.contains("invCrate"))
      value = "0";
    string += value;
  }); 

  return string;
}

function changeCrates(number) {
  let num = number.textContent;

  if(lastCrateClicked.classList.contains('obsText')) {
    document.getElementById(lastCrateClicked.parentElement.id).childNodes[0].textContent = num;
  }
  else {
    document.getElementById(lastCrateClicked.id).textContent = num;
  }

}

function hideCrate(hideButton) {
  console.log(lastCrateClicked);
  if(lastCrateClicked.classList.contains('obsText')) {
    if(hideButton.classList.contains("inv")) {
      document.getElementById(lastCrateClicked.id).parentElement.classList.add('invCrate');
    }
    
    else {
      document.getElementById(lastCrateClicked.id).parentElement.classList.remove('invCrate');
    }
  }

  else {
    if(hideButton.classList.contains("inv")) {
      document.querySelector('#' + lastCrateClicked.id).classList.add('invCrate');
    }
    
    else {
      document.querySelector('#' + lastCrateClicked.id).classList.remove('invCrate');
    }
  }
  
}

document.querySelector('.crateInvChoice').addEventListener('click', e => {
  document.querySelector('.crateInvChoice').classList.toggle('inv');

  hideCrate(document.querySelector('.crateInvChoice'));
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

/*

let seed =convertStringIntoGrid(tabDim, obsTab, crateTab)
document.cookie = "seed="+seed; 
*/

function convertStringIntoGrid(str) {

  let dim = Number(str[0]);

  let obs = [];
  let crate = [];

  for(let i = 0; i < dim * 4; i++) {
    obs.push(Number(str[1 + i]));
  }

  for(let i = 0; i < dim**2; i++) {
    crate.push(Number(str[i + 1 + dim*4]));
  }

  return [dim, obs, crate];

}


function setCookie(cname, cvalue, exdays) {
  const d = new Date();
  d.setTime(d.getTime() + (exdays*24*60*60*1000));
  let expires = "expires="+ d.toUTCString();
  document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
}

function getCookie(cname) {
  let name = cname + "=";
  let decodedCookie = decodeURIComponent(document.cookie);
  let ca = decodedCookie.split(';');
  for(let i = 0; i <ca.length; i++) {
    let c = ca[i];
    while (c.charAt(0) == ' ') {
      c = c.substring(1);
    }
    if (c.indexOf(name) == 0) {
      return c.substring(name.length, c.length);
    }
  }
  return "";
}

function displayObservators() {
  let size = Number(getCookie("CON_dim"));

  var count = 0;

  for(let i = 0; i < size; i++) {
    let element = document.querySelector(`#pos_${i + 1}_0`);
    element.innerHTML += `<div id="obs_${count}" class="obsText rotate00">${ obsTab[count] == 0 ? '' : obsTab[count] }</div>`;

    count++;
  }

  for(let i = 0; i < size; i++) {
    let element = document.querySelector(`#pos_${size + 1}_${i + 1}`);
    element.innerHTML += `<div id="obs_${count}" class="obsText rotate270">${ obsTab[count] == 0 ? '' : obsTab[count] }</div>`;

    count++;
  }

  for(let i = size - 1; i >= 0; i--) {
    let element = document.querySelector(`#pos_${i + 1}_${size + 1}`);
    element.innerHTML += `<div id="obs_${count}" class="obsText rotate180">${ obsTab[count] == 0 ? '' : obsTab[count] }</div>`;

    count++;
  }

  for(let i = size - 1; i >= 0; i--) {
    let element = document.querySelector(`#pos_0_${i + 1}`);
    element.innerHTML += `<div id="obs_${count}" class="obsText rotate90">${ obsTab[count] == 0 ? '' : obsTab[count] }</div>`;

    count++;
  }
}

function displayCrates() {
  let size = Number(getCookie("CON_dim"));

  document.querySelectorAll(".cratePlace").forEach((crate, index) => {
    crate.textContent = crateTab[index] == 0 ? "" : crateTab[index];
  })
}

function addEventListeners() {  
  document.querySelectorAll('.cratePlace').forEach((elem, index) => {

    elem.addEventListener('click', e => {

      if(crateTab[index].hidden == true)
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
}

function generateGridBody() {
  let size = Number(getCookie("CON_dim"));

  let grid = document.querySelector("#mainPlate");
  
  grid.classList = 'dim' + size;
  grid.innerHTML = '';

  
  for(let i = 0; i < (size + 2)**2; i++) {

    let x = i % (size + 2);
    let y = Math.floor(i / (size + 2));

    if((x == 0 || x == size + 1) && (y == 0 || y == size + 1)) {
      grid.innerHTML += `<div id="pos_${x}_${y}"></div>`;
    }

    else if(x == 0) {
      grid.innerHTML += `<div id="pos_${x}_${y}" class="obs rotate270"></div>`;
    }

    else if(x == size + 1) {
      grid.innerHTML += `<div id="pos_${x}_${y}" class="obs rotate90"></div>`;
    }

    else if(y == 0) {
      grid.innerHTML += `<div id="pos_${x}_${y}" class="obs rotate00"></div>`;
    }

    else if(y == size + 1) {
      grid.innerHTML += `<div id="pos_${x}_${y}" class="obs rotate180"></div>`;
    }

    else {
      grid.innerHTML += `<div id="pos_${x}_${y}" class="cratePlace"></div>`;
    }

  }

  // Creates virtual elements
  /*
  for(let i = 0; i < size * 4; i++) {
    obsTab.push(0);
  }
  
  for(let i = 0; i < size; i++) {
    crateTab.push([]);
    for(let j = 0; j < size; j++) {
      crateTab[i].push({
        val: 0,
        hidden: false
      });
    }
  }
   

  // Creates physical elements
  for(let y = 0; y < size + 2; y++) {
    for(let x = 0; x < size + 2; x++) {
      gameSet.innerHTML += `<div id="pos_${x - 1}_${y - 1}"></div>`
    }
  }


  // OBSERVATORS DISPLAYING
  var count = 0;

  for(let i = 0; i < size; i++) {
    let element = document.querySelector(`#pos_${i}_-1`);
    element.innerHTML += `<div id="obs_${count}" class="obsText rotate00">${obsTab[count]}</div>`;

    count++;
  }

  for(let i = 0; i < size; i++) {
    let element = document.querySelector(`#pos_${size}_${i}`);
    element.innerHTML += `<div id="obs_${count}" class="obsText rotate270">${obsTab[count]}</div>`;

    count++;
  }

  for(let i = size - 1; i >= 0; i--) {
    let element = document.querySelector(`#pos_${i}_${size}`);
    element.innerHTML += `<div id="obs-${count}" class="obsText rotate180">${obsTab[count]}</div>`;

    count++;
  }

  for(let i = size - 1; i >= 0; i--) {
    let element = document.querySelector(`#pos_-1_${i}`);
    element.innerHTML += `<div id="obs-${count}" class="obsText rotate90">${obsTab[count]}</div>`;

    count++;
  }
  */
}

function displayMessage() {
  let value = getCookie('CON_message');

  if(value == "")
    value = "No information"

  document.querySelector(".messageBox").textContent = value;

  setCookie('CON_message', '', 0);
}

function generateAutoGrid() {

  let difficulty = document.querySelector('[name="difficulty"]:checked').value;
  let size = document.querySelector('[name="sizeGrid"]:checked').value;

  setCookie("CON_dim",  size,       365);
  setCookie("CON_diff", difficulty, 365);

  displayMessage();

  // Wish an empty grid
  if(difficulty == 4) {

    obsTab = [];
    crateTab = [];

    for(let i = 0; i < size*4; i++) { obsTab.push(0); }
    for(let i = 0; i < size**2; i++) { crateTab.push(0); }

    generateGridBody();

    displayObservators();

    displayCrates();

    addEventListeners();

    setCookie("CON_grid", "", 0);
  }

  else {

    if(getCookie("CON_grid") != "") {

      let res = convertStringIntoGrid(getCookie("CON_grid"));

      obsTab = res[1];
      crateTab = res[2];

      generateGridBody();

      displayObservators();

      displayCrates();

      addEventListeners();

      setCookie("CON_grid", "", 0);
    }

    else {
      setCookie("CON_grid", "", 0);

      document.location.reload();
    } 
  }
}

function saveGrid() {
  let crates = document.querySelectorAll(".cratePlace");
  let obss = document.querySelectorAll(".obs");

  let difficulty = document.querySelector('[name="difficulty"]:checked').value;
  let size = document.querySelector('[name="sizeGrid"]:checked').value;

  setCookie("CON_dim",  size,       365);
  setCookie("CON_diff", difficulty, 365);

  let stringTab = createStringGrid(size, obss, crates);

  setCookie("CON_grid", stringTab, 365);

  console.log(stringTab)

  // document.location.reload();
}

generateAutoGrid();