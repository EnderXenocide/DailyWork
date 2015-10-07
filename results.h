#ifndef RESULTS_H
#define RESULTS_H


struct Result
{
    wxDateTime date;
    wxString text;
    Result( wxDateTime d, wxString t) : date( d ), text( t ) {};
};


struct ResultComp
{
  bool operator()(const Result& lhs, const Result& rhs) {
    return lhs.date > rhs.date; //de la plus recente à la plus vielle
  }
};

#endif // RESULTS_H
