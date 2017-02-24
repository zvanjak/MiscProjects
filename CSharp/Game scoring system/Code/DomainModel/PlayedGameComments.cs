using System;
using System.Collections.Generic;
using System.Text;

namespace ZGSS.DomainModel
{
  public class PlayedGameComments
  {
    List<Comment> _listComments = new List<Comment>();

    public Comment this[int i]
    {
      get
      {
        return _listComments[i];
      }
    }

  }
}
