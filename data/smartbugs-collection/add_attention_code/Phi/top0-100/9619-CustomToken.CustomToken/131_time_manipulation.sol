 

 pragma solidity ^0.4.15;

 

contract EtherLotto {

     
    uint constant TICKET_AMOUNT = 10;

     
    uint constant FEE_AMOUNT = 1;

     
    address public bank;

     
    uint public pot;

     
    function EtherLotto() {
        bank = msg.sender;
    }

     
     
    function play() payable {

         
        assert(msg.value == TICKET_AMOUNT);

         
        pot += msg.value;

         
         
        var random = uint(sha3(block.timestamp)) % 2;

         
        if (random == 0) {

             
            bank.transfer(FEE_AMOUNT);

             
            msg.sender.transfer(pot - FEE_AMOUNT);

             
            pot = 0;
        }
    }

}

library SafeMath {

  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract DetailedERC20 {
  string public name;
  string public symbol;
  uint8 public decimals;

  function DetailedERC20(string _name, string _symbol, uint8 _decimals) public {
    name = _name;
    symbol = _symbol;
    decimals = _decimals;
  }
}

contract BasicToken {
  using SafeMath for uint256;

  mapping(address => uint256) balances;

  uint256 totalSupply_;

}

contract CustomToken is BasicToken, DetailedERC20 {

    function CustomToken(string _name, string _symbol, uint8 _decimals, uint maximumSupply) DetailedERC20(_name, _symbol, _decimals) {

        totalSupply_ = totalSupply_.add(maximumSupply * (10 ** uint(decimals)));
        balances[msg.sender] = balances[msg.sender].add(totalSupply_);
    }

}
