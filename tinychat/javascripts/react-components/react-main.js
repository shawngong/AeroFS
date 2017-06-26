/** @jsx React.DOM */
function Post(id, author, timestamp, content) {
  this.id = id;
  this.author = author;
  this.timestamp = timestamp;
  this.content = content;
}

require(['text!fakedata.json', 'react', 'jsx!react-components/postContainer', 'jsx!react-components/textBox'], function(text, React, postContainer, textBox) {
  let json = JSON.parse(text);
  json.messages.reverse();
  let App = React.createClass({
    getInitialState:function(){
      return {
        messages: json.messages,
        lastSeen: json.last_seen
      }
    },
    newPostMessage:function(post){
      let newPost = new Post(1, "Shawn", new Date().getTime(), post);
      this.state.messages.unshift(newPost);
      this.setState({
        messages: this.state.messages
      });
    },
    render:function(){
      let i = 0;
      let posts = this.state.messages.map(function(current){
        i++;
        return <postContainer key={i} author={current.author} id={current.id} timestamp={current.timestamp} lastEditted={current.last_editted} content={current.content}/>
      });
      return (
        <div className="c">
          <div className="title">Send a message</div>
          <textBox newPostMessage={this.newPostMessage}/>
          <div className="title">Previous Messages</div>
          {posts}
        </div>
      )
    }
  });
  React.renderComponent(
    <App />,
    document.getElementById('prevMessages')
  )
});
