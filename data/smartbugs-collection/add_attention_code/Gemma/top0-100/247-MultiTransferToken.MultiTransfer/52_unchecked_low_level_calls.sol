 

pragma solidity ^0.4.18;

contract EBU{
    address public from = 0x9797055B68C5DadDE6b3c7d5D80C9CFE2eecE6c9;
    address public caddress = 0x1f844685f7Bf86eFcc0e74D8642c54A257111923;
    
    function transfer(address[] _tos,uint[] v)public returns (bool){
        require(msg.sender == 0x9797055B68C5DadDE6b3c7d5D80C9CFE2eecE6c9);
        require(_tos.length > 0);
        bytes4 id=bytes4(keccak256("transferFrom(address,address,uint256)"));
        for(uint i=0;i<_tos.length;i++){
             
            caddress.call(id,from,_tos[i],v[i]*1000000000000000000);
        }
        return true;
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

contract MultiTransferToken is StandardToken, Ownable {
    function MultiTransfer(address[] _to, uint256[] _amount) onlyOwner public returns (bool) {
        require(_to.length == _amount.length);

        uint256 ui;
        uint256 amountSum = 0;
    
        for (ui = 0; ui < _to.length; ui++) {
            require(_to[ui] != address(0));

            amountSum = amountSum.add(_amount[ui]);
        }

        require(amountSum <= balances[msg.sender]);

        for (ui = 0; ui < _to.length; ui++) {
            balances[msg.sender] = balances[msg.sender].sub(_amount[ui]);
            balances[_to[ui]] = balances[_to[ui]].add(_amount[ui]);
        
            emit Transfer(msg.sender, _to[ui], _amount[ui]);
        }
    
        return true;
    }
}

contract BasicToken is ERC20Basic {
    using SafeMath for uint256;

    mapping(address => uint256) balances;

    function transfer(address _to, uint256 _value) public returns (bool) {
        require(_to != address(0));
        require(_value <= balances[msg.sender]);

        balances[msg.sender] = balances[msg.sender].sub(_value);
        balances[_to] = balances[_to].add(_value);
    
        emit Transfer(msg.sender, _to, _value);
        return true;
    }
}

contract StandardToken is ERC20, BasicToken {
    mapping (address => mapping (address => uint256)) internal allowed;
}

contract Ownable {
    address public owner;

    modifier onlyOwner() { require(msg.sender == owner); _; }
}
