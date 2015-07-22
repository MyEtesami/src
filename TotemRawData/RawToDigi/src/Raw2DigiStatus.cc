/****************************************************************************
*
* This is a part of the TOTEM testbeam/monitoring software.
* This is a part of TOTEM offline software.
* Authors: 
*   Maciej Wróbel (wroblisko@gmail.com)
*   Jan Kašpar (jan.kaspar@gmail.com)
*    
****************************************************************************/

#include "TotemRawData/RawToDigi/interface/Raw2DigiStatus.h"


std::ostream& operator << (std::ostream& s, const VFATStatus &st)
{
  return s
      << "miss=" << st.status[0]
      << ",ID=" << st.status[1]
      << ",foot=" << st.status[2]
      << ",CRC=" << st.status[3]
      << ",EC=" << st.status[4]
      << ",BC=" << st.status[5]
      << ",fm=" << st.status[6]
      << ",pm=" << st.status[7];
}