var enterInGame = true;
var displayFront = false;

document.querySelector("#crateStackLogo").onload = () => {
	document.querySelector("#crateStackLogo").classList.toggle("show");
	document.querySelector("#pressKeyText").classList.toggle("show");

	displayFront = true;
}

setTimeout(() => {
	if(!displayFront) {
		document.querySelector("#crateStackLogo").classList.toggle("show");
		document.querySelector("#pressKeyText").classList.toggle("show");
	}
}, 1500)

document.addEventListener('keydown', e => {
	if(enterInGame) {
		document.querySelector('.backDis').classList.toggle('hidden');
		document.querySelector('.frontDis').classList.toggle('hidden');

		enterInGame = false;

		document.querySelector("body").style.overflow = "auto";
	}
})