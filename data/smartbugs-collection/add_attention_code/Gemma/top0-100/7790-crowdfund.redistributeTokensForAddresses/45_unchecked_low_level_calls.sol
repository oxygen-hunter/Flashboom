 

pragma solidity ^0.4.11;  

contract Owned {
    function Owned() {
        owner = msg.sender;
    }

    address public owner;

     
     
     
    modifier onlyOwner { if (msg.sender == owner) _; }

    function changeOwner(address _newOwner) onlyOwner {
        owner = _newOwner;
    }

     
     
     
    function execute(address _dst, uint _value, bytes _data) onlyOwner {
         
        _dst.call.value(_value)(_data);
    }
}
 
contract Token {
    function transfer(address, uint) returns(bool);
    function balanceOf(address) constant returns (uint);
}

contract TokenSender is Owned {
    Token public token;  
    uint public totalToDistribute;

    uint public next;


    struct Transfer {
        address addr;
        uint amount;
    }

    Transfer[] public transfers;

    function TokenSender(address _token) {
        token = Token(_token);
    }

     
    uint constant D160 = 0x0010000000000000000000000000000000000000000;

     
     
     
     
     
     
    function fill(uint[] data) onlyOwner {

         
        if (next>0) throw;

        uint acc;
        uint offset = transfers.length;
        transfers.length = transfers.length + data.length;
        for (uint i = 0; i < data.length; i++ ) {
            address addr = address( data[i] & (D160-1) );
            uint amount = data[i] / D160;

            transfers[offset + i].addr = addr;
            transfers[offset + i].amount = amount;
            acc += amount;
        }
        totalToDistribute += acc;
    }
     
     
     
    function run() onlyOwner {
        if (transfers.length == 0) return;

         
        uint mNext = next;

         
        next = transfers.length;

        if ((mNext == 0 ) && ( token.balanceOf(this) != totalToDistribute)) throw;

        while ((mNext<transfers.length) && ( gas() > 150000 )) {
            uint amount = transfers[mNext].amount;
            address addr = transfers[mNext].addr;
            if (amount > 0) {
                if (!token.transfer(addr, transfers[mNext].amount)) throw;
            }
            mNext ++;
        }

         
        next = mNext;
    }


     
     
     

    function hasTerminated() constant returns (bool) {
        if (transfers.length == 0) return false;
        if (next < transfers.length) return false;
        return true;
    }

    function nTransfers() constant returns (uint) {
        return transfers.length;
    }

    function gas() internal constant returns (uint _gas) {
        assembly {
            _gas:= gas
        }
    }

}

library SafeMath {

  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract crowdfund {

    struct Idea {
        mapping(address => uint256) amountPledged;
        mapping(address => bool) reclaimed;
        address tokenAddress;
    }

    Idea[] public ideas;
    uint256 public FAILED_STATUS;
    
    event UserRegainedAmountAtIndex(address user,uint256 amount,uint256 index);

    function crowdfund() {
        FAILED_STATUS=4;
    }

    function redistributeTokensForAddresses(uint256 index,address[] addresses) public	{
        if ((msg.sender==ideas[index].creator) || (msg.sender==ideas[index].host))	{
            if (ideas[index].status==FAILED_STATUS)	{
                for(uint256 i = 0; i < addresses.length; i++) {
                    address addr=addresses[i];
                    if (!ideas[index].reclaimed[addr])    { 
                        uint256 reclaimAmount=ideas[index].amountPledged[addr];
                        if (reclaimAmount>0)    { 
                            ideas[index].reclaimed[addr]=true; 
                            emit UserRegainedAmountAtIndex(addr,reclaimAmount,index);
                            if(! token(ideas[index].tokenAddress).transfer(addr,reclaimAmount)) revert();
                        }
                    }
                }    
            }
        }
    }
}

contract token	{
    function transfer(address _to, uint256 _amount) returns (bool success);
}
