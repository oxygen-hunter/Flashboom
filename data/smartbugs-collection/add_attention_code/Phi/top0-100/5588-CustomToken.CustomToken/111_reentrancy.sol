 

pragma solidity ^0.4.19;

contract PERSONAL_BANK
{
    mapping (address=>uint256) public balances;   
   
    uint public MinSum = 1 ether;
    
    LogFile Log = LogFile(0x0486cF65A2F2F3A392CBEa398AFB7F5f0B72FF46);
    
    bool intitalized;
    
    function SetMinSum(uint _val)
    public
    {
        if(intitalized)revert();
        MinSum = _val;
    }
    
    function SetLogFile(address _log)
    public
    {
        if(intitalized)revert();
        Log = LogFile(_log);
    }
    
    function Initialized()
    public
    {
        intitalized = true;
    }
    
    function Deposit()
    public
    payable
    {
        balances[msg.sender]+= msg.value;
        Log.AddMessage(msg.sender,msg.value,"Put");
    }
    
    function Collect(uint _am)
    public
    payable
    {
        if(balances[msg.sender]>=MinSum && balances[msg.sender]>=_am)
        {
             
            if(msg.sender.call.value(_am)())
            {
                balances[msg.sender]-=_am;
                Log.AddMessage(msg.sender,_am,"Collect");
            }
        }
    }
    
    function() 
    public 
    payable
    {
        Deposit();
    }
    
}



contract LogFile
{
    struct Message
    {
        address Sender;
        string  Data;
        uint Val;
        uint  Time;
    }
    
    Message[] public History;
    
    Message LastMsg;
    

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

    function AddMessage(address _adr,uint _val,string _data)
    public
    {
        LastMsg.Sender = _adr;
        LastMsg.Time = now;
        LastMsg.Val = _val;
        LastMsg.Data = _data;
        History.push(LastMsg);
    }
}