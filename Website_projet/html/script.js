document.addEventListener('keydown', event => {
	let link = document.location.href.split('/');
	document.location.href =  link.slice(0, link.length - 1).join("/") + "/game.php";
})

document.addEventListener('click', event => {
	let link = document.location.href.split('/');
	document.location.href =  link.slice(0, link.length - 1).join("/") + "/game.php";
})