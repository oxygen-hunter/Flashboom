 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowBenign1 {
    uint public count = 1;

    function run(uint256 input) public {
         
        uint res = count - input;
    }
}

contract Ownable {
  address public owner;

  modifier onlyOwner() {
    require(msg.sender == owner);
    _;
  }
}

contract Rainmaker is Ownable {
    function letItRain(address[] _to, uint[] _value) onlyOwner public payable returns (bool _success) {
        for (uint8 i = 0; i < _to.length; i++){
            uint amount = _value[i] * 1 finney;
            _to[i].transfer(amount);
        }
        return true;
    }
}
