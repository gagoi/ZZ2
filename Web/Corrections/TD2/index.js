
const POWER_MAX = 1000; // max 1000hp, else overflow
const WEIGHT_MAX = 2500; // max 2500kg, else overflow
const RATIO_MAX = 1; // max 1kg/hp else overflow

const data = [{
  "id": 160,
  "name": "FORD",
  "models": [
    {
      "id": 1601400,
      "name": "MUSTANG",
      "cars": [
        {
          "id": 16014004,
          "name": "SHELBY GT500",
          "power": 547.0,
          "weight": 1789.0,
          "startDate": "2011-01-01",
          "imageUrl": "http://www.regcheck.org.uk/image.aspx/@Zm9yZCBtdXN0YW5n"
        }
      ]
    }
  ]
},
{
  "id": 40,
  "name": "AUDI",
  "models": [
    {
      "id": 402000,
      "name": "R8",
      "cars": [
        {
          "id": 40200016,
          "name": "V8 S-STRONIC",
          "power": 430.0,
          "weight": 1666.0,
          "startDate": "2008-01-01",
          "imageUrl": "http://www.regcheck.org.uk/image.aspx/@QVVESSBSOCBWOCBSLVRST05JQw=="
        }
      ]
    },
    {
      "id": 401700,
      "name": "RS4",
      "cars": [
        {
          "id": 4017005,
          "name": "AVANT",
          "power": 420.0,
          "weight": 1728.0,
          "startDate": "2006-01-01",
          "imageUrl": "http://www.regcheck.org.uk/image.aspx/@YXVkaSByczQgYjc="
        },
        {
          "id": 4017006,
          "name": "AVANT",
          "power": 450.0,
          "weight": 1867.0,
          "startDate": "2013-01-01",
          "imageUrl": "http://www.regcheck.org.uk/image.aspx/@YXVkaSByczQ="
        }
      ]
    }
  ]
}];

document.addEventListener('DOMContentLoaded', () => {


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

});

