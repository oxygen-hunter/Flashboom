 

 
pragma solidity ^0.4.10;

contract EtherStore {

    uint256 public withdrawalLimit = 1 ether;
    mapping(address => uint256) public lastWithdrawTime;
    mapping(address => uint256) public balances;

    function depositFunds() public payable {
        balances[msg.sender] += msg.value;
    }

    function withdrawFunds (uint256 _weiToWithdraw) public {
        require(balances[msg.sender] >= _weiToWithdraw);
         
        require(_weiToWithdraw <= withdrawalLimit);
         
        require(now >= lastWithdrawTime[msg.sender] + 1 weeks);
         
        require(msg.sender.call.value(_weiToWithdraw)());
        balances[msg.sender] -= _weiToWithdraw;
        lastWithdrawTime[msg.sender] = now;
    }
 }

library SafeMath {
    function sub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function add(uint256 a, uint256 b) internal pure returns (uint256) {
        uint256 c = a + b;
        assert(c >= a && c >= b);
        return c;
    }
}

contract YomiToken {
    using SafeMath for uint256;

    uint256 constant public teamReserve = 100000000e18;
    uint256 constant public foundationReserve = 200000000e18;
    uint256 public lockReleaseDate6Month;
    uint256 public lockReleaseDate1Year;
    address public teamAddr;
    address public foundationAddr;
    mapping (address => uint256) balances;
    mapping (address => bool) public frozenAccounts;
    
    event Transfer(address indexed _from, address indexed _to, uint256 _value);
    
    function _transfer(address _from, address _to, uint256 _value) internal {
        require(_to != 0x0);
        
        if (_from == teamAddr && now < lockReleaseDate6Month) {
            require(balances[_from].sub(_value) >= teamReserve);
        }
        
        if (_from == foundationAddr && now < lockReleaseDate1Year) {
            require(balances[_from].sub(_value) >= foundationReserve);
        }
        
        require(balances[_from] >= _value);
        require(balances[_to] + _value > balances[_to]);
        require(!frozenAccounts[_from]);
        require(!frozenAccounts[_to]);

        uint256 previousBalances = balances[_from].add(balances[_to]);
        balances[_from] = balances[_from].sub(_value);
        balances[_to] = balances[_to].add(_value);
        emit Transfer(_from, _to, _value);
        assert(balances[_from] + balances[_to] == previousBalances);
    }
}
