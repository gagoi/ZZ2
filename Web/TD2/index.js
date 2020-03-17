
const POWER_MAX = 1000; // max 1000hp, else overflow
const WEIGHT_MAX = 2500; // max 2500kg, else overflow
const RATIO_MAX = 1; // max 1kg/hp else overflow

async function fetchAPI(url)
{
  const response = await fetch(url);
  return response.json();
}

function getData()
{
  return fetchAPI("https://sports-cars-accountable-civet.cfapps.io/api/cars");
}

document.addEventListener('DOMContentLoaded', () => {
  /*
  fetch("https://sports-cars-accountable-civet.cfapps.io/api/cars").then(respons => respons.json()).then(data => load(data));
  */

  load();
  const header = document.querySelector('header-component').addEventListener('clear', {});
});

async function load()
{
  const data = await fetchAPI("https://sports-cars-accountable-civet.cfapps.io/api/cars");
  const modelContent = document.querySelector('.model-content');

  data.forEach(brand => {

    brand.models.forEach(model => {

      // instance of ModelComponent is created as an HTML element
      const modelComponent = document.createElement('model-component');
      // add css class to apply styles
      modelComponent.classList.add('card');

      // we can push brand and model as attributes because they are strings
      modelComponent.setAttribute('brand', brand.name);
      modelComponent.setAttribute('model', model.name);
      modelComponent.setAttribute('image-url', model.cars[0].imageUrl);

      // push car as property because it is an array
      modelComponent.cars = model.cars.map(car => ({
        name: car.name,
        year: car.startDate ? car.startDate.match(/\d{4}/g)[0] : undefined,
        ratio: Math.round(car.weight * 10 / car.power) / 10,
        weight: car.weight,
        power: car.power,
      }));

      // add model element to the DOM
      modelContent.appendChild(modelComponent);
    });
  });
}