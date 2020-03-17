export default async function getTemplate(filepath) {
  let response = await fetch(filepath);
  let txt = await response.text();

  let html = new DOMParser().parseFromString(txt, 'text/html');
  return html.querySelector('template');
}
