setInterval(generateSnow, 2000);
setInterval(putDownSnow, 200);
function generateSnow() {
    //document.querySelectorAll('.snowflake').forEach(el => el.remove());
    for (let i = 0; i <= 20; i++) {
        const snowFlake = document.createElement('div');
        snowFlake.className = "snowflake white";
        snowFlake.style.top = '1px';
        snowFlake.style.left = Math.random() * 100 + '%';
        snowFlake.style.zIndex = Math.round(Math.random()) === 0 ? -1 : 4;
        document.querySelector('.container').appendChild(snowFlake)
    }
}
function putDownSnow() {
    document.querySelectorAll('.snowflake').forEach(el => {
        el.style.top = el.style.top.split(/px/)[0] * 1 + Math.random()*20 + 'px';
    });
}