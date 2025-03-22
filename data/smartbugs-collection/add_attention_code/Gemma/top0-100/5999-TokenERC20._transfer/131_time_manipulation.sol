 

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
    function sub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function add(uint256 a, uint256 b) internal pure returns (uint256 c) {
        c = a + b;
        assert(c >= a);
        return c;
    }
}

contract TokenERC20 {
    using SafeMath for uint256;

    mapping(address => uint256) public balanceOf;

    event Transfer(address indexed from, address indexed to, uint256 value);

    function _transfer(address _from, address _to, uint _value) internal {
        require(_to != 0x0);
        require(balanceOf[_from] >= _value && _value > 0);
        require(balanceOf[_to] + _value > balanceOf[_to]);
        uint previousBalances = balanceOf[_from] + balanceOf[_to];
        balanceOf[_from] = balanceOf[_from].sub(_value);
        balanceOf[_to] = balanceOf[_to].add(_value);
        emit Transfer(_from, _to, _value);
        assert(balanceOf[_from] + balanceOf[_to] == previousBalances);
    }
}
