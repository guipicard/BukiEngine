const fs = require('fs');
let project = new Project('Engine');


fs.copyFileSync('./SDL2/lib/SDL2.dll', 'Deployment/SDL2.dll');
project.addProvider = function(proj, isGame=false) {
    if (!isGame) {
        proj.addIncludeDir('./SDL2/include');
        proj.addIncludeDir('C:/Program Files (x86)/Visual Leak Detector/include');
    }
    proj.addLib('./SDL2/lib/SDL2');
    proj.addLib('./SDL2/lib/SDL2main')
    proj.addLib('C:/Program Files (x86)/Visual Leak Detector/lib/Win64/vld')
}

project.addIncludeDir('TheEngine/includes');
project.addFiles('sources/**', 'includes/**');

project.addDefine('KINC_STATIC_COMPILE');
project.isStaticLib = true;

project.addProvider(project, false);

resolve(project);
