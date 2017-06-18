// Mixing jQuery and Node.js code in the same file? Yes please!

$(function(){
	var os = require('os');
	var prettyBytes = require('pretty-bytes');

	$('.stats').append('Number of cpu cores: <span>' + os.cpus().length + 'asdf</span>');
	$('.stats').append('Free memory: <span>' + prettyBytes(os.freemem()) + 'adf</span>');


	var gui = require('nw.gui');
});

$("#group_proceccing_1").click(function(){
	alert(
		$("#list_input_folder").val() + "\n"

		+ $("#output_folder").val() + " : " + $("#output_folder").prop("checked") + "\n"
		+ $("#copy").val() + " : " + $("#copy").prop("checked") + "\n"
		+ $("#move").val() + " : " + $("#move").prop("checked") + "\n"
		+ $("#ubrat_copy").val() + " : " + $("#ubrat_copy").prop("checked") + "\n"
		+ $("#global").val() + " : " + $("#global").prop("checked") + "\n"
		+ $("#local").val() + " : " + $("#local").prop("checked") + "\n"
		
		
		);

	var folders = $("#list_input_folder").val().split('\n');
	jQuery.each(folders, function(i, val)
	{
	}); 
});