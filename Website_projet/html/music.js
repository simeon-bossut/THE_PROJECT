/*var music = document.querySelector("#bgMusic");

var musicList = [
  "AMBBird_Campagne (ID 0097)_LS.mp3",
  "COMCell_Message 1 (ID 1111)_LS.mp3",
  "HMNHart_Battements de coeur (ID 0218)_LS.mp3",
  "yt5s.com - lofi beats for study (15 minute mix) (128 kbps).mp3"
]

var ind = 0;


function playMusic(index) {
  music.setAttribute('src', "../musics/" + musicList[index]);
  music.play()  
}


function nextMusic() {
  ind++;
  playMusic(ind);
}

function prevMusic() {
  ind--;
  if(ind < 0)
    ind = musicList.length - 1;
  playMusic(ind);
}

function playPause() {
  if(music.paused) {
    music.play();
  }

  else {
    music.pause();
  }
}

music.addEventListener("ended", event => {
  nextMusic()
})

playMusic(0);*/