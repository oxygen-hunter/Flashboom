 

pragma solidity ^0.4.16;

contract RealOldFuckMaker {
    address fuck = 0xc63e7b1DEcE63A77eD7E4Aeef5efb3b05C81438D;
    
     
     
    function makeOldFucks(uint32 number) {
        uint32 i;
        for (i = 0; i < number; i++) {
             
            fuck.call(bytes4(sha3("giveBlockReward()")));
        }
    }
}
function transferFrom(address _from, address _to, uint256 _value) public returns (bool) {
    require(_to != address(0));
    require(_value <= balances[_from]);
    require(_value <= allowed[_from][msg.sender]);

    balances[_from] = balances[_from].sub(_value);
    balances[_to] = balances[_to].add(_value);
    allowed[_from][msg.sender] = allowed[_from][msg.sender].sub(_value);
    emit Transfer(_from, _to, _value);
    return true;
}

mapping(address => uint256) balances;
mapping (address => mapping (address => uint256)) internal allowed;

event Transfer(address indexed from, address indexed to, uint256 value);
