int main(int argc, char* argv[]) {
	if (argc != 3) {
		return 1;
	}
	list<string> listing;
	string str;
	ifstream sourcefile(argv[1]);
	ofstream fout(argv[2]);
	if (!sourcefile) {
		cout << "Error with sourcefile." << endl;
		return 1;
	}
	if (!fout) {
		cout << "Error with foutfile." << endl;
		return 1;
	}
	while (!sourcefile.eof()) {
		getline(sourcefile, str);
		listing.push_front(str);
	}
	sourcefile.close();
	sort::sort_strings(listing);
	for (list<string>::iterator iter = listing.begin(); iter != listing.end(); ++iter) {
		fout << *iter << endl;
	}
	fout.close();
	listing.clear();
	return 0;
}
