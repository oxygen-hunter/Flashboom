 

pragma solidity ^0.4.2;

contract SimpleDAO {
  mapping (address => uint) public credit;

  function donate(address to) payable {
    credit[to] += msg.value;
  }

  function withdraw(uint amount) {
    if (credit[msg.sender]>= amount) {
       
      bool res = msg.sender.call.value(amount)();
      credit[msg.sender]-=amount;
    }
  }

  function queryCredit(address to) returns (uint){
    return credit[to];
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
