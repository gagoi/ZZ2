let i = 0;
const modelContents = document.querySelectorAll('.model-content');
data.forEach(brand => {
  brand.models.forEach(model => {
    modelContents[i].querySelector('h2').innerText = brand.name + ' ' + model.name;
    model.cars.forEach(car =>{
      modelContents[i].querySelector('img').src = car.imageUrl;
      car.year = car.startDate.substring(0, 4);
      car.ratio = Math.round(car.weight / car.power);
      // name + year
      modelContents[i].querySelector('h3').innerText = `${car.name} ${car.year}`;
      // weight
      modelContents[i].querySelector('.weight').innerText = car.weight;
      modelContents[i].querySelector('.bar-weight').style.width = (car.weight * 100 / WEIGHT_MAX) + '%';
      // power 
      modelContents[i].querySelector('.power').innerText = car.power;
      modelContents[i].querySelector('.bar-power').style.width = (car.power * 100 / POWER_MAX) + '%';
      // ratio
      modelContents[i].querySelector('.ratio').innerText = Math.round(car.weight / car.power * 100) / 100;
      modelContents[i].querySelector('.bar-ratio').style.width = (RATIO_MAX * 100 / car.ratio) + '%';
    })
    i++;
  });
});