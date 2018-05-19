const char* webpage_front PROGMEM =R"=====(<!DOCTYPE html>
<html>
<style>

input[type=text]{
    width: 40%;
    padding: 12px 20px;
    margin: 8px 0;
    display: inline-block;
    border: 1px solid #ccc;
    box-sizing: border-box;
}

button {
    background-color: #4CAF50;
    color: white;
    padding: 14px 20px;
    margin: 8px 0;
    border: none;
    cursor: pointer;
    width: 30%;
}

h2 {font-family: "Trebuchet MS", Helvetica, sans-serif; font-size: 300%;}
b  {font-family: "Comic Sans MS", cursive, sans-serif; font-size: 95%;}

.imgcontainer {
    text-align: center;
    margin: 24px 0 42px 0;
}

img.avatar {
    width: 40%;  
    border-radius: 50%;
    box-shadow: 0 8px 16px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19);
}

.idcontainer {
  width:100%;
  margin: 8px 0;  
  align:center;
}

.button1 {
font-size: 100%;
background-color: #99ff99;
border: 2px solid #006600;
padding: 10px 10px;
color: #000000;
text-align: center;
cursor: pointer;
font-weight:bold;
font-family: trebuchet ms,helvetica,sans-serif;
display: inline-block;
border-radius: 4px;
width: 200px;
transition: all 0.5s;
margin: 5px;
box-shadow: 0 8px 16px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19);
}

.button1 span {
  cursor: pointer;
  display: inline-block;
  position: relative;
  transition: 0.5s;
}

.button1 span:after {
  content: '\00bb';
  position: absolute;
  opacity: 0;
  top: 0;
  right: -20px;
  transition: 0.5s;
}

.button1:hover span {
  padding-right: 25px;
}

.button1:hover span:after {
  opacity: 1;
  right: 0;
}

.button2 {
font-size: 100%;
background-color: #ffffff;
border: 2px solid #006600;
padding: 10px 10px;
color: #000000;
cursor: pointer;
border-radius: 25px;
font-weight:bold;
font-family: trebuchet ms,helvetica,sans-serif;
box-shadow: 0 8px 16px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19);
}

</style>
<title>SRC-SERVERS</title>

<head>
<link rel="icon" 
      type="image/png" 
      href="https://www.penguincomputing.com/wp-content/uploads/2016/07/cloud%20icon%203.png">
</head>

<body>

<form method="POST" action="/submit">

<center><h2><b>Login Form</h2>

  <div class="imgcontainer">
    <img src="https://preview.ibb.co/h3L2xw/271225_510042515692493_345280553_o.png" class="avatar">
  </div>
  
  <div class="idcontainer">
    <label><b>Email-ID</b></label>
    <input type="text" placeholder="Eg: xyz@gmail.com" name="id" class="button2">
    <button type="submit" class="button1">Submit</button><br><br>
  </div>
</form>

</body>
</html>
)=====";
