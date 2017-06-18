// Mixing jQuery and Node.js code in the same file? Yes please!

$(function(){
	var os = require('os');
	var prettyBytes = require('pretty-bytes');

	$('.stats').append('Number of cpu cores: <span>' + os.cpus().length + 'asdf</span>');
	$('.stats').append('Free memory: <span>' + prettyBytes(os.freemem()) + 'adf</span>');


	var gui = require('nw.gui');
});



function data_of_form ()
{
	var arr_data = {};
	arr_data["list_input_folder"] = $("#list_input_folder").val();
	arr_data["output_folder"] = $("#output_folder").val();
	arr_data["type_mover"] = ($("#copy").prop("checked")) ? "copy" : "move";
	arr_data["remove_copies"] = $("#ubrat_copy").prop("checked");
	arr_data["type_remove_copies"] = ($("#global").prop("checked")) ? "global" : "local";

	return arr_data;
}
$("#group_proceccing_1").click(function(){
	var arr_data = {};
	var arr_data = data_of_form();
	var str_folders = arr_data["list_input_folder"];
	var folders = str_folders.split('\n');
	var text = "";
	jQuery.each(folders, function(i, val)
	{
		text += val + "\n";
	});
	alert(text);
});