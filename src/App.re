let str = ReasonReact.string;

type route =
  | Picture1
  | Picture2
  | Picture3
  | Picture4
  | Todos
  | Todo(string);

type state = {route};

type action =
  | ChangeRoute(route);

let reducer = (action, _state) =>
  switch (action) {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  reducer,
  initialState: () => {route: Picture1},
  didMount: self => {
    let watcherID =
      ReasonReact.Router.watchUrl(url =>
        switch (url.path) {
        | [] => self.send(ChangeRoute(Picture1))
        | ["picture_2"] => self.send(ChangeRoute(Picture2))
        | ["picture_3"] => self.send(ChangeRoute(Picture3))
        | ["picture_4"] => self.send(ChangeRoute(Picture4))
        | ["todos"] => self.send(ChangeRoute(Todos))
        | ["todo", id] => self.send(ChangeRoute(Todo(id)))
        | _ => self.send(ChangeRoute(Picture1))
        }
      );
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
  render: self =>
    <div>
      <ul>
        <li> <Link href="picture_1"> (str("picture 1")) </Link> </li>
        <li> <Link href="picture_2"> (str("picture 2")) </Link> </li>
        <li> <Link href="picture_3"> (str("picture 3")) </Link> </li>
        <li> <Link href="picture_4"> (str("picture 4")) </Link> </li>
        <li> <Link href="todos"> (str("Todos")) </Link> </li>
      </ul>
      <div>
        (
          switch (self.state.route) {
          | Picture1 =>
            <img
              src="https://images.pexels.com/photos/1026230/pexels-photo-1026230.jpeg?auto=compress&cs=tinysrgb&h=350"
              alt="picture 1"
            />
          | Picture2 =>
            <img
              src="https://images.pexels.com/photos/1406340/pexels-photo-1406340.jpeg?auto=compress&cs=tinysrgb&h=350"
              alt="picture 2"
            />
          | Picture3 =>
            <img
              src="https://images.pexels.com/photos/1309052/pexels-photo-1309052.jpeg?auto=compress&cs=tinysrgb&h=350"
              alt="picture 3"
            />
          | Picture4 =>
            <img
              src="https://images.pexels.com/photos/1386988/pexels-photo-1386988.jpeg?auto=compress&cs=tinysrgb&h=350"
              alt="picture 4"
            />
          | Todos => <Todos greeting="Hello" />
          | Todo(id) => <Todo id />
          }
        )
      </div>
    </div>,
};