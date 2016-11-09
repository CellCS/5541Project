int main(int argc, char * argv [])
{
	string filename;
	switch (argc){
	case 1:      // no file name
		break;
	case 2:      //read from argument string
		filename = argv[1];
		break;
	default:
		cout<<("too many arguments - all discarded") <<endl;
		filename.clear();
		break;
	}
	LineEditor ed(filename);     //create an editor object
	ed.run();    // run our editor
	return 0;
}
