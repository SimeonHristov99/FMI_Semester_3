var gl;
var glprog;

function getContext(id)
{
    var canvas = document.getElementById(id);
    
    if(!canvas)
    {
        alert("No canvas with id=\""+id+"\" was found!");
        return null;
    }
    
    var context = canvas.getContext("webgl");
    
    if(!context)
    {
        alert("WebGL context not found!");
    }
    
    return context;
}

function getShader(id, type)
{
    var shader = gl.createShader(type);
    var source = document.getElementById(id).text;
    
    gl.shaderSource(shader, source);
    gl.compileShader(shader);
    
    if(!gl.getShaderParameter(shader, gl.COMPILE_STATUS))
    {
        alert(gl.getShaderInfoLog(shader));
        return null;
    }
    
    return shader;
}

function getProgram(idv, idf)
{
    var vShader = getShader(idv, gl.VERTEX_SHADER);
    var fShader = getShader(idf, gl.FRAGMENT_SHADER);
    
    if(!vShader || !fShader)
    {
        return null;
    }
    
    var shaderProgram = gl.createProgram();
    
    gl.attachShader(shaderProgram,vShader);
	gl.attachShader(shaderProgram,fShader);
    
    gl.linkProgram(shaderProgram);
    
    if (!gl.getProgramParameter(shaderProgram,gl.LINK_STATUS))
	{
		alert(gl.getProgramInfoLog(shaderProgram));
		return null;
	}

	gl.useProgram(shaderProgram);
	return shaderProgram;
}