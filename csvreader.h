#ifndef CSVREADER_H
#define CSVREADER_H

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class CSVRow
{
    public:
        std::string const& operator[](std::size_t index) const
        {
            return m_data[index];
        }
        std::size_t size() const
        {
            return m_data.size();
        }
        void readNextRow(std::istream& str)
        {
            std::string         line;
            std::getline(str, line);
            std::replace(std::begin(line),std::end(line),'\t',' ');

            std::stringstream   lineStream(line);
            std::string         cell;

            m_data.clear();
            while(std::getline(lineStream, cell, separator))
            {
                m_data.push_back(cell);
            }
            // This checks for a trailing comma with no data after it.
            if (!lineStream && cell.empty())
            {
                // If there was a trailing comma then add an empty element.
                m_data.push_back("");
            }
        }

        void setSeparator(char sep){
            this->separator = sep;
            return;
        }

        char getSeparator(){
            return this->separator;
        }

        void addCell(std::string str){
            m_data.push_back(str);
        }


    private:
        std::vector<std::string>    m_data;
        char separator = '-';
};

inline std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

class CSVIterator
{
    public:
        typedef std::input_iterator_tag     iterator_category;
        typedef CSVRow                      value_type;
        typedef std::size_t                 difference_type;
        typedef CSVRow*                     pointer;
        typedef CSVRow&                     reference;

        CSVIterator(std::istream& str, char sep)  :m_str( str.good() ? &str : NULL ) {m_sep=sep; ++(*this); }
        CSVIterator()                   :m_str(NULL) {}

        // Pre Increment
        CSVIterator& operator++()               {if (m_str) { m_row.setSeparator(m_sep); if (!((*m_str) >> m_row)){m_str = NULL;}}return *this;}
        // Post increment
        CSVIterator operator++(int)             {CSVIterator    tmp(*this);++(*this);return tmp;}
        CSVRow const& operator*()   const       {return m_row;}
        CSVRow const* operator->()  const       {return &m_row;}

        bool operator==(CSVIterator const& rhs) {return ((this == &rhs) || ((this->m_str == NULL) && (rhs.m_str == NULL)));}
        bool operator!=(CSVIterator const& rhs) {return !((*this) == rhs);}



    private:
        std::istream*       m_str;
        CSVRow              m_row;
        char                m_sep;
};

class CSVFile
{
    public:
        CSVFile(std::string path_to_file): filepath(path_to_file), separator('-'), headersRow(0) {Init();}
        CSVFile(std::string path_to_file, char sep): filepath(path_to_file), separator(sep), headersRow(0) {Init();}
        CSVFile(std::string path_to_file, char sep, uint headRow): filepath(path_to_file), separator(sep), headersRow(headRow) {Init();}


        void Init(){
            Read();
            EqualizeRowLengths();
        }

        void Read()
        {
           try{
               std::ifstream file(filepath);
               for(CSVIterator loop(file, separator); loop != CSVIterator(); ++loop){
                   rows.push_back((*loop));
                   numberOfColumns = (*loop).size() > numberOfColumns ? (*loop).size() : numberOfColumns;
               }
            }catch(const std::exception& e){
               std::cout << e.what() << std::endl;
           }
        }

        void EqualizeRowLengths()
        {
            for(uint i = 0; i < NumberOfRows(); i++){
                while(rows[i].size() < NumberOfColumns()) {
                    rows[i].addCell("");
                }
            }

        }


        CSVRow const operator[](std::size_t index_i) const
        {
            return rows[index_i];
        }

        std::size_t NumberOfRows() const
        {
            return rows.size();
        }

        std::size_t NumberOfColumns() const
        {
            return this->numberOfColumns;
        }

        void set_separator(char sep){
            this->separator = sep;
            return;
        }

        char get_separator(){
            return this->separator;
        }

        CSVRow get_headers(){
            if(headersRow > 0){
                return this->rows[headersRow-1];
            }else{
                return CSVRow();
            }
        }

        CSVRow get_row(int i){
            return this->rows[i];
        }

    private:
        std::string filepath;
        char separator = '-';
        uint headersRow = 0;
        uint numberOfColumns = 0;
        std::vector<CSVRow>    rows;

};

#endif // CSVREADER_H
