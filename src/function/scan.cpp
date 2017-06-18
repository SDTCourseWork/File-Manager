#include "scan.h"
 




void SCAN ()
{
	using boost::interprocess;
	 
	/****** ... and somewhere at very important program ***********/
	 
	const boost::filesystem::path base_dir (".");
	std::string extension (".zzz");
	     
	for (boost::filesystem::directory_iterator it (base_dir); it != boost::filesystem::directory_iterator (); ++it)
	{       
	    boost::filesystem::path p = it->path ();
	    if(boost::filesystem::is_regular_file (it->status ()) && boost::filesystem::extension (it->path ()) == extension)
	    {           
	    //mapping & processing
	        file_mapping file_mapper(it->path().string(), read_only);
	        mapped_region mapped_reg(file_mapper, read_only);
	        double * double_pointer = (double *)mapped_reg.get_address();
	        size_t elements  = region.get_size()/sizeof(double);
	         
	        // to get name only without extension
	        string fname =boost::filesystem::basename (p);
	        cout << fname << endl;
	    }
	}
}
