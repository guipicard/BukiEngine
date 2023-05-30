let project = new Project('Buki Engine');

project.addIncludeDir('TheEngine/includes');
project.addFile('TheGame/**');
project.setDebugDir('Deployment');

project.flatten();

const otherproj = await project.addProject('TheEngine');

otherproj.addProvider(project, true);

resolve(project);
