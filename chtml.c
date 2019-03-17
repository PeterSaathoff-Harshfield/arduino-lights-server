#include <avr/pgmspace.h>

const char index[] = "<!DOCTYPE HTML>\n\
<head>\n\
	<script src=\"https://code.jquery.com/jquery-3.3.1.min.js\" integrity=\"sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8=\" crossorigin=\"anonymous\"></script>\n\
</head>\n\
<html>\n\
  <body style=\"font-family: 'Helvetica'; text-align: center;\">\n\
    <h1 style=\"font-size: 4em;\">Lights</h1>\n\
    <span style=\"font-size: 3em\" id=\"powerStatus\"> </span>\n\
    <span style=\"font-size: 3em\">&nbsp</span>\n\
    <button style=\"font-size: 4em; border: none; background-color: #ddd\" onclick=\"javascript: update('/powerToggle');\" class=\"btn btn-primary mb-2\" id=\"powerButton\">&#8204</button>\n\
    </br>\n\
    </br>\n\
    <button style=\"font-size: 3em; border: none; background-color: #ddd\" onclick=\"javascript: update('/white');\" class=\"btn btn-primary mb-2\">White</button>\n\
    <button style=\"font-size: 3em; border: none; background-color: #ddd\" onclick=\"javascript: update('/solidColors');\" class=\"btn btn-primary mb-2\">Solid</button>\n\
    <button style=\"font-size: 3em; border: none; background-color: #ddd\" onclick=\"javascript: update('/random');\" class=\"btn btn-primary mb-2\">Random</button>\n\
    </br>\n\
    <button style=\"font-size: 3em; border: none; background-color: #ddd\" onclick=\"javascript: update('/spectrum');\" class=\"btn btn-primary mb-2\">Spectrum</button>\n\
    <button style=\"font-size: 3em; border: none; background-color: #ddd\" onclick=\"javascript: update('/gradient');\" class=\"btn btn-primary mb-2\">Gradient</button>\n\
    </br>\n\
    <button style=\"font-size: 3em; border: none; background-color: #ddd\" onclick=\"javascript: update('/flow');\" class=\"btn btn-primary mb-2\">Flow</button>\n\
    <button style=\"font-size: 3em; border: none; background-color: #ddd\" onclick=\"javascript: update('/red');\" class=\"btn btn-primary mb-2\">Red</button>\n\
    </br>\n\
    </br>\n\
    <button style=\"font-size: 3em; border: none; background-color: #ddd;\" onclick=\"javascript: update('/left');\" class=\"btn btn-primary mb-2\">&#8592</button>\n\
    <button style=\"font-size: 3em; border: none; background-color: #ddd;\" onclick=\"javascript: update('/right');\" class=\"btn btn-primary mb-2\">&#8594</button>\n\
	\n\
    <script>\n\
      function update(value) {\n\
          $.ajax({\n\
              method: 'get',\n\
              url: value,\n\
              success: function(data) {\n\
                  \n\
                  if (data.error) {\n\
                    \n\
                  }\n\
                  else {\n\
					\n\
	                var redColor = data[\"r\"];\n\
                    var greenColor = data[\"g\"];\n\
                    var blueColor = data[\"b\"];\n\
                    \n\
                    $(\"body\").css(\"background-color\", \"rgb(\" + String(parseInt(String(redColor))) + \",\" + String(parseInt(String(greenColor))) + \",\" + String(parseInt(String(blueColor))) + \")\");\n\
                    $(\"#powerButton\").text(String(data[\"powerButtonText\"]));\n\
					$(\"#powerStatus\").text(String(data[\"powerStatus\"]));\n\
					\n\
					if (redColor + greenColor + blueColor < 255) {\n\
						$(\"h1\").css(\"color\", \"white\");\n\
						$(\"#powerStatus\").css(\"color\", \"white\");\n\
					}\n\
					else {\n\
						$(\"h1\").css(\"color\", \"black\");\n\
						$(\"#powerStatus\").css(\"color\", \"black\");\n\
					}\n\
					\n\
					if (data[\"powerStatus\"] == \"Off\") {\n\
						$(\"body\").css(\"background-color\", \"black\");\n\
						$(\"h1\").css(\"color\", \"white\");\n\
						$(\"#powerStatus\").css(\"color\", \"white\");\n\
					}\n\
					\n\
					\n\
                  }\n\
              }\n\
          });\n\
      }\n\
    </script>\n\
	<script>\n\
		update('/json');\n\
		setInterval(function() {\n\
			update('/json');\n\
		}, 1000);\n\
	</script>\n\
	\n\
  </body>\n\
</html>\n\
";

