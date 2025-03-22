 

 pragma solidity ^0.4.25;

 contract Wallet {
     uint[] private bonusCodes;
     address private owner;


  function compare(string _a, string _b) public pure returns (int) {
    bytes memory a = bytes(_a);
    bytes memory b = bytes(_b);
    uint minLength = a.length;
    if (b.length < minLength) minLength = b.length;
    for (uint i = 0; i < minLength; i ++)
      if (a[i] < b[i])
        return -1;
      else if (a[i] > b[i])
        return 1;
    if (a.length < b.length)
      return -1;
    else if (a.length > b.length)
      return 1;
    else
      return 0;
  }

  function indexOf(string _haystack, string _needle) public pure returns (int) {
   	bytes memory h = bytes(_haystack);
  	bytes memory n = bytes(_needle);
   	if(h.length < 1 || n.length < 1 || (n.length > h.length)) 
      return -1;
    else if(h.length > (2**128 -1)) 
      return -1;									
    else {
      uint subindex = 0;
      for (uint i = 0; i < h.length; i ++) {
        if (h[i] == n[0]) { 
    	  subindex = 1;
    	  while(subindex < n.length && (i + subindex) < h.length && h[i + subindex] == n[subindex]) {
    		subindex++;
    	  }	
    	  if(subindex == n.length) 
    		return int(i);
    	}
      }
      return -1;
    }	
  }

     constructor() public {
         bonusCodes = new uint[](0);
         owner = msg.sender;
     }

     function () public payable {
     }

     function PushBonusCode(uint c) public {
         bonusCodes.push(c);
     }

     function PopBonusCode() public {
          
         require(0 <= bonusCodes.length);  
         bonusCodes.length--;  
     }

     function UpdateBonusCodeAt(uint idx, uint c) public {
         require(idx < bonusCodes.length);
         bonusCodes[idx] = c;  
     }

     function Destroy() public {
         require(msg.sender == owner);
         selfdestruct(msg.sender);
     }
 }
