var fileInput = document.getElementById('file');
var divCadre = document.getElementById("cadre");
var divStruct = document.getElementById("structure");
var divCritere = document.getElementById("critere");
var divZone = document.getElementById("zoneCheckboxes");
var divType = document.getElementById("typeCheckboxes");
var divCadre = document.getElementById("cadre");
var textInSelectZone = document.getElementById("optionZone");
var textInSelectType = document.getElementById("optionType");

var radioTroubleSevere = document.getElementById("severe");
var radioTroubleLeger = document.getElementById("leger");

var structures = new Array();
var criteres = new Array();
var bools = new Array();
var zones = new Array();
var types = new Array();

divCadre.style.display = "none";

fileInput.addEventListener('change', function(e) {

    deleteAll();

    var reader = new FileReader();

    reader.addEventListener('load', function(e) {
        divCadre.style.display = "grid";
        lines = reader.result.split(/\r\n|\r|\n/);
        createCriteres(lines[0]);
        createTypes(lines[0]);
        lines.splice(0, 1);
        createStructures(lines);
        hideAndShow();
    }, false);

    reader.readAsText(fileInput.files[0], 'ISO-8859-1');

}, false);

class Structure {
    constructor(name, address, num, site, zone, score, leger, severe, boolArray, boolType) {
        this.name = name;
        this.address = address;
        this.num = num;
        this.site = site;
        this.boolArray = boolArray;
        this.zone = zone;
        this.score = score;
        this.isSevere = severe;
        this.isLeger = leger;
        this.boolType = boolType;
        this.hasToBeShowed = false;

        this.div = document.createElement("div");
        this.div.setAttribute("class", "divStruct");

        this.divName = document.createElement("div");
        this.divAddress = document.createElement("div");
        this.divNum = document.createElement("div");
        this.divScore = document.createElement("div");
        this.link = document.createElement("a");
        this.separateur = document.createElement("hr");

        this.divName.appendChild(document.createTextNode(this.name));
        this.div.appendChild(this.divName);

        this.divAddress.appendChild(document.createTextNode(this.address));
        this.div.appendChild(this.divAddress);

        this.divNum.appendChild(document.createTextNode(this.num));
        this.div.appendChild(this.divNum);

        if (this.site != "") {
            this.link.appendChild(document.createTextNode("Site Web"));
            this.link.setAttribute("href", "http://" + this.site);
            this.link.setAttribute("target", "_blank");
            this.div.appendChild(this.link);
        }

        this.separateur.style.color = "#000000";
        this.div.appendChild(this.separateur);
    }

    show() {
        this.div.style.visibility = "visible";
        this.div.style.height = "auto";
        this.div.style.padding = "5px";
    };

    hide() {
        this.div.style.visibility = "hidden";
        this.div.style.height = "0px";
        this.div.style.padding = "0px";
    };
}

class Critere {
    constructor(name, force) {
        this.name = name;
        this.force = force;

        this.div = document.createElement("div");
        this.div.setAttribute("class", "critere");

        this.input = document.createElement("input");
        this.input.setAttribute("type", "checkbox");
        this.input.setAttribute("id", this.name);
        this.input.setAttribute("class", "inputCritere");

        this.input.addEventListener("change", modify, false);

        this.label = document.createElement("label");
        this.label.appendChild(document.createTextNode(this.name))
        this.label.setAttribute("for", this.name);

        this.div.appendChild(this.input);
        this.div.appendChild(this.label);

        divCritere.appendChild(this.div);
    }
}

class Zone {
    constructor(name) {
        this.name = name;

        this.div = document.createElement("div");

        this.input = document.createElement("input");
        this.input.setAttribute("type", "checkbox");
        this.input.setAttribute("id", this.name);

        this.input.addEventListener("change", modify, false);

        this.label = document.createElement("label");
        this.label.setAttribute("for", this.name);
        this.label.appendChild(document.createTextNode(this.name));

        this.div.appendChild(this.input);
        this.div.appendChild(this.label);

        divZone.appendChild(this.div);
    }
}

class Type {
    constructor(name) {
        this.name = name;

        this.div = document.createElement("div");

        this.input = document.createElement("input");
        this.input.setAttribute("type", "checkbox");
        this.input.setAttribute("id", this.name);

        this.input.addEventListener("change", modify, false);

        this.label = document.createElement("label");
        this.label.setAttribute("for", this.name);
        this.label.appendChild(document.createTextNode(this.name));

        this.div.appendChild(this.input);
        this.div.appendChild(this.label);

        divType.appendChild(this.div);
    }
}

function createTypes(string) {
    var typeNames = string.split(";");
    types.push(new Type(typeNames[7]));
    types.push(new Type(typeNames[8]));
    types.push(new Type(typeNames[9]));
}

function createCriteres(string) {
    var critereNames = string.split(";");
    for (var i = 10; i < critereNames.length; i++) {
        if (critereNames[i] != "") {
            var critereParam = critereNames[i].split("|");
            criteres.push(new Critere(critereParam[0], critereParam[1]));
            bools.push(false);
        }
    }
    document.getElementById("structure").style.height = new String(document.getElementById("critere").offsetHeight + "px");
}

function createStructures(stringArray) {
    for (var i = 0; i < stringArray.length; i++) {
        if (stringArray[i] != "") {
            var structStrings = stringArray[i].split(";");

            var boolArray = new Array();
            for (var j = 0; j < criteres.length; j++) {
                boolArray.push(structStrings[10 + j] == "1");
            }

            var boolType = new Array();
            boolType.push(structStrings[7] == "1");
            boolType.push(structStrings[8] == "1");
            boolType.push(structStrings[9] == "1");

            if (structStrings[4] == "")
                structStrings[4] = "Zone non définie";
            if (!isInZones(structStrings[4])) {
                zones.push(new Zone(structStrings[4]));
            }

            structures.push(new Structure(structStrings[0], structStrings[1], structStrings[2], structStrings[3], structStrings[4], "0", structStrings[5] == "1", structStrings[6] == "1", boolArray, boolType));
        }
    }

    structures.sort((a, b) => b.score - a.score);
    for (var i = 0; i < structures.length; i++) {
        divStruct.appendChild(structures[i].div);
    }
}

function deleteCriteres() {
    for (var i = 0; i < criteres.length; i++) {
        divCritere.removeChild(criteres[i].label);
    }
    bools = [];
    criteres = [];
}

function deleteStructures() {
    for (var i = 0; i < structures.length; i++) {
        divStruct.removeChild(structures[i].div);
    }
    structures = [];
}

function deleteZones() {
    for (var i = 0; i < zones.length; i++) {
        divZone.removeChild(zones[i].label);
    }
    zones = [];
}

function deleteTypes() {
    for (var i = 0; i < types.length; i++) {
        divType.removeChild(types[i].div);
    }
    types = [];
}

function modify() {

    // Mise a jour du bandeau des zones
    while (textInSelectZone.firstChild) {
        textInSelectZone.removeChild(textInSelectZone.firstChild);
    }
    var nb = 0;
    for (var i = 0; i < zones.length; i++) {
        if (zones[i].input.checked) {
            textInSelectZone.appendChild(document.createTextNode((nb > 0 ? ", " : "") + zones[i].name));
            nb++;
        }
    }
    if (nb == 0) {
        textInSelectZone.appendChild(document.createTextNode("-- Choisir les zones --"));
    }

    // Mise a jour du bandeau des types
    while (textInSelectType.firstChild) {
        textInSelectType.removeChild(textInSelectType.firstChild);
    }
    nb = 0;
    for (var i = 0; i < types.length; i++) {
        if (types[i].input.checked) {
            textInSelectType.appendChild(document.createTextNode((nb > 0 ? ", " : "") + types[i].name));
            nb++;
        }
    }
    if (nb == 0) {
        textInSelectType.appendChild(document.createTextNode("-- Choisir les types --"));
    }

    for (var i = 0; i < structures.length; i++) {

        // Tests criteres
        var hasCriteres = false;
        for (var j = 0; j < criteres.length; j++) {
            if (criteres[j].input.checked)
                hasCriteres = hasCriteres || structures[i].boolArray[j]; // passage de intersection à union pour les critères
        }

        // Tests types
        var hasType = false;
        for (var j = 0; j < types.length; j++) {
            if (types[j].input.checked)
                hasType = hasType || structures[i].boolType[j];
        }

        // Test zone
        var hasZone = false;
        for (var j = 0; j < zones.length; j++) {
            if (zones[j].name == structures[i].zone) {
                hasZone = zones[j].input.checked;
            }
        }

        // Test trouble
        var hasTrouble = (structures[i].isSevere && radioTroubleSevere.checked) || (structures[i].isLeger && radioTroubleLeger.checked);

        // Conclusion
        if (hasCriteres && hasZone && hasTrouble && hasType)
            structures[i].hasToBeShowed = true;
        else
            structures[i].hasToBeShowed = false;
    }
}

function hideAndShow() {
    for (var i = 0; i < structures.length; i++) {
        if (structures[i].hasToBeShowed)
            structures[i].show();
        else
            structures[i].hide();
    }
}

function deleteAll() {
    deleteCriteres();
    deleteStructures();
    deleteZones();
}

function isInZones(z) {
    var exist = false;
    var i = 0;
    while (i < zones.length) {
        exist = exist || (zones[i].name == z);
        i++;
    }
    return exist;
}





var expandedZone = false;

function showZoneCheckboxes() {
    var checkboxes = document.getElementById("zoneCheckboxes");
    if (!expandedZone) {
        checkboxes.style.display = "block";
        expandedZone = true;
    } else {
        checkboxes.style.display = "none";
        expandedZone = false;
    }
}

var expandedType = false;

function showTypeCheckboxes() {
    var checkboxes = document.getElementById("typeCheckboxes");
    if (!expandedType) {
        checkboxes.style.display = "block";
        expandedType = true;
    } else {
        checkboxes.style.display = "none";
        expandedType = false;
    }
}