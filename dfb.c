#include <stdio.h>
#include <unistd.h>
#include <directfb.h>

static IDirectFB *dfb = NULL;
static IDirectFBSurface *primary = NULL;
static int screen_width  = 0;
static int screen_height = 0;

#define DFBCHECK(x...)                                         \
  {                                                            \
    DFBResult err = x;                                         \
                                                               \
    if (err != DFB_OK)                                         \
      {                                                        \
        fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ ); \
        DirectFBErrorFatal( #x, err );                         \
      }                                                        \
  }

int main (int argc, char **argv)
{
  DFBSurfaceDescription dsc;

  /* Initialize Direct FB */
  DFBCHECK (DirectFBInit (&argc, &argv));

  /* Create Super Interface */
  DFBCHECK (DirectFBCreate (&dfb));

  /* Go Full Screen */
  DFBCHECK (dfb->SetCooperativeLevel (dfb, DFSCL_FULLSCREEN));  
  //DFBCHECK(dfb->SetCooperativeLevel(dfb, DFSCL_NORMAL));

  /* Flippable Primary Surface */
  dsc.flags = DSDESC_CAPS;
  dsc.caps  = DFBSurfaceCapabilities(DSCAPS_PRIMARY | DSCAPS_FLIPPING);

  /* Create Surface */
  DFBCHECK (dfb->CreateSurface( dfb, &dsc, &primary ));

  /* Get Screen Resolution of Primary Surface */
  DFBCHECK (primary->GetSize (primary, &screen_width, &screen_height));

  DFBCHECK (primary->FillRectangle (primary, 0, 0, screen_width/2, screen_height/2));

  DFBCHECK (primary->SetColor (primary, 0x80, 0x80, 0xff, 0xff));
  DFBCHECK (primary->DrawLine (primary,
			                      0, screen_height / 2,
			       screen_width - 1, screen_height / 2));
  DFBCHECK (primary->Flip (primary, NULL, DFBSurfaceFlipFlags(0)));
/*
  for (;;) {
    char text[4096];
    fgets(text, sizeof(text), stdin);
    strtok(text, "\n");

    if (!strcmp(text, "QUIT")) 
      break;
    else if (!strcmp(text, "FLIP")) {
      primary->SetColor(primary, 0x20, 0x20, 0xff, 0xff);
    } else {
      primary->SetColor(primary, 0x40, 0x40, 0xff, 0xff);
    }
  } */
  sleep (5);

  /* cleanup primary and super interface */
  primary->Release( primary );
  dfb->Release( dfb );

  return 23;
}
