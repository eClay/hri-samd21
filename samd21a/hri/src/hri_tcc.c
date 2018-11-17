#include "hri/tcc.h"


void HRI_TCC_Initialize( void )
{
  for( hri_tcc_instance_t timer = 0; timer < HRI_TCC_NUM_INSTANCES; timer++ )
  {
    HRI_TCC_SoftwareReset( timer );
  }
}
